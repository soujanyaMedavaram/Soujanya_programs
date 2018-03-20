# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../../utils.h"
# include "ipc.h"
# include "../sb.h"
# include "proto.h"
# include <signal.h>
# include <stdlib.h>
# include <sys/ipc.h>
# include <sys/msg.h>

struct msgbuf {
	long mtype;
	union {
		char mtext[1];
		struct info {
			int client_chan;
			char user_text[1];
		} info;
	} data;
};

struct ipc {
	int msq_id;
	int channel;
	int server;
	int max_msg_size;
	struct msgbuf msg_buf;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	IPC * ipc_id;
	int id;

	id = msgget ( getuid ( ), 0600 );
	if ( id != -1 )
		return (IPC *)1;
	ipc_id = malloc ( sizeof ( IPC ) +
				OFFSET (struct info, user_text) + max_msg_size - 1 );
	if ( ipc_id == NULL )
		return NULL;
	ipc_id->channel = ++max_channel;
	ipc_id->max_msg_size = max_msg_size + OFFSET (struct info, user_text);
	ipc_id->msq_id = msgget ( getuid ( ), 0600 | IPC_CREAT | IPC_EXCL );
	if ( ipc_id->msq_id == -1 )
		return NULL;
	ipc_id->server  = 1;
	return ipc_id;
}

IPC * open_ipc ( int channel, int max_msg_size ) {
	IPC * ipc_id; 
	int id;
	
	id = msgget ( getuid ( ), 0600 );
	if ( id < 0 )
		return ( IPC *)1;
	ipc_id = malloc ( sizeof ( IPC ) +
					OFFSET (struct info, user_text) + max_msg_size - 1 );
	if ( ipc_id == NULL )
		return NULL;
	ipc_id->channel = channel;
	ipc_id->max_msg_size = max_msg_size + OFFSET (struct info, user_text);
	ipc_id->server  = 0;
	ipc_id->msq_id  =  msgget ( getuid ( ), 0600 );
	return ipc_id;
}

int send_ipc ( IPC * ipc_id, void * data, int size, int channel ) {
	ipc_id->msg_buf.mtype = ipc_id->server ? channel : 1;
	if ( !ipc_id->server )
		ipc_id->msg_buf.data.info.client_chan = ipc_id->channel;
	memcpy ( ipc_id->msg_buf.data.info.user_text, data, size );
	if ( msgsnd ( ipc_id->msq_id, & ipc_id->msg_buf,
				OFFSET (struct info, user_text) + size , 0 ) < 0 )
		return IPC_FAIL;
	return IPC_SUCCESS;
}

int receive_ipc ( IPC * ipc_id, void * data ) {
	int size, chan;

	chan = ipc_id->server ? 1 : ipc_id->channel;
	if ( ( size = msgrcv ( ipc_id->msq_id, & ipc_id->msg_buf,
				ipc_id->max_msg_size, chan, 0 ) ) < 0 ) 
		return IPC_FAIL;
	memcpy ( data, ipc_id->msg_buf.data.info.user_text, 
					size - OFFSET ( struct info, user_text ) );
	return ipc_id->server ? ipc_id->msg_buf.data.info.client_chan : IPC_SUCCESS;
}

void close_ipc ( IPC * ipc_id ) {
	if ( ipc_id->server )
		msgctl ( ipc_id->msq_id, IPC_RMID, NULL );
	free ( ipc_id );
}

int server_client ( IPC *ipc_id, int chan,int action ) {
	static int * occupied, max_chan;
	int i;

	switch ( action ) {
		case START :
			max_chan = chan;
			occupied = calloc ( ++max_chan, sizeof( int ) );
			occupied[0]= 1;	// Never used
			occupied[1] = 1;	// Request channel
			occupied[2] = 1;	// Channel No. reply channel */
			return  IPC_SUCCESS;
		case ADD :
			for ( i = 3; i < max_chan; i++ )
				if ( !occupied[i] ) break;
			if ( i < max_chan ) {
				occupied[i] = 1;
				return i ;
			} else return  -1; 

		case REM :
			if ( chan < 3 || chan >= max_chan )
				return -1 ;		// ERROR !!  Don't know what to do
			occupied[chan] = 0; 
			return IPC_SUCCESS; 
	}
}
