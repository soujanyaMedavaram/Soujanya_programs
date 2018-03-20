# include <stdio.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../../../utils.h"
# include "../ipc.h"
# include "../../sb.h"
# include "../proto.h"
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>

# define CH_MAX	100

struct ipc {
	int * fd;
	int channel;
	int server;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	int i, j;
	char fifo [CH_MAX];
	IPC * ipc_id;

	if ( !access ( "FIFO1", F_OK ) )
		return ( IPC * )1;  // server already started
	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->channel = max_channel;
	ipc_id->fd = malloc ( (max_channel + 1) * sizeof ( int ) );
		// fd[0] is not used
	ipc_id->server  = 1;
	for ( i = 1; i <= max_channel; i++ ) {
		sprintf ( fifo , "FIFO%d", i );
		if ( mkfifo ( fifo , 0600 ) < 0 && EEXIST != errno ) {
			for ( j = 1; j < i; j++ ) {
				sprintf ( fifo , "FIFO%d", j );
				close ( ipc_id->fd[j] );
				unlink  ( fifo  );
			}
			return NULL;
		}
		ipc_id->fd[i] = open ( fifo , O_RDWR );
		if ( ipc_id->fd[i] < 0 ) {
			for ( j = 1; j < i; j++ ) {
				close ( ipc_id->fd[j] );
				sprintf ( fifo , "FIFO%d", j );
				unlink ( fifo  );
			}
			return NULL;
		}
	}
	return ipc_id;
}

IPC * open_ipc ( int channel, int max_msg_size ) {
	IPC * ipc_id;
	char fifo [CH_MAX];

	if ( access ( "FIFO1", F_OK )  < 0 )
		return  ( IPC *) 1; // server not started.
	sprintf ( fifo , "FIFO%d", channel );
	if ( access ( fifo, F_OK ) < 0 )
		return (IPC *) -1;
	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->channel = channel;
	ipc_id->server  = 0;
	ipc_id->fd = malloc ( 2 * sizeof ( int ) );
	ipc_id->fd[1] = open ( "FIFO1", O_WRONLY );
	if ( ipc_id->fd[1] < 0 ) 
		return NULL;
	ipc_id->fd[0] = open ( fifo, O_RDONLY );
	if ( ipc_id->fd[0] < 0 )
		return NULL;
	return ipc_id;
}

int send ( IPC * ipc_id, void * data, int size, int channel ) {
	struct iovec v[3]; int pos;

	pos = 0;
	v[pos].iov_base = (char *) & size;
	v[pos++].iov_len  = sizeof (size);
	if ( !ipc_id->server ) {
		v[pos].iov_base = (char *)&ipc_id->channel;
		v[pos++].iov_len  = sizeof (ipc_id->channel);
	}
	v[pos].iov_base = data;
	v[pos++].iov_len  = size;
	if ( writev ( ipc_id->fd[channel], v, pos ) == -1 )
		printf ( "\n <%s>\n", strerror ( errno ));
	return IPC_SUCCESS;
}

int receive ( IPC * ipc_id, void * data ) {
	int size, chan, rx_chan;

	chan = ipc_id->server ? 1 : 0;
	if ( read ( ipc_id->fd[chan], & size, sizeof (int) ) != sizeof (int) )
		return IPC_FAIL;
	if ( ipc_id->server ) 
		if ( read ( ipc_id->fd[chan], & rx_chan, sizeof (int) ) !=
					sizeof (int) )
			return IPC_FAIL;
	if ( read ( ipc_id->fd[chan], data, size ) != size )
		return IPC_FAIL ;
	return ipc_id->server ? rx_chan : IPC_SUCCESS;
}

void close_ipc ( IPC * ipc_id ) {
	int i;
	char fifo [CH_MAX];
	
	if ( ipc_id->server ) {
		for ( i = 1; i <= ipc_id->channel; i++ ) {
			close ( ipc_id->fd[i] );
			sprintf ( fifo , "FIFO%d", i );
			unlink ( fifo  );
		}
	}
	else {
		close ( ipc_id->fd[0] );
		close( ipc_id->fd[1] );
	}
	free ( ipc_id->fd );
	free ( ipc_id );
}
