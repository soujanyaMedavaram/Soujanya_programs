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
# include <stdlib.h>
# include <signal.h>
# include <sys/ipc.h>
# include <sys/shm.h>

# define IDLE		0
# define WRITTEN	1


typedef struct {
	int status;
	int chan_no;
	int size;
	char msg[1];
} SHM_CHANNEL;

struct ipc {
	int msg_id;
	int sem_id;
	int channel;
	int server;
	int max_msg_size;
	int size;			// one communication channel size
	char * shm;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	IPC * ipc_id; 
	volatile SHM_CHANNEL * p;
	int id, size, i;

	max_channel++;
	size = max_msg_size + sizeof (volatile SHM_CHANNEL) - 1;
	id = shmget ( getuid ( ), size * max_channel, 0600 );
	if ( id != -1 ) return ( IPC *) 1;
	ipc_id = malloc ( sizeof ( IPC ) );
	if ( ipc_id == NULL )  return NULL;
	ipc_id->size = size;
	ipc_id->max_msg_size = max_msg_size;
	ipc_id->msg_id = shmget ( getuid (), size * max_channel, 0600 | IPC_CREAT );
	if ( ipc_id->msg_id == -1 ) return NULL;
	ipc_id->server = 1;
	ipc_id->shm = shmat ( ipc_id->msg_id, NULL, SHM_RND );
	if ( ipc_id->shm == (void *)-1 ) {
		remove_shm:
			shmctl ( ipc_id->msg_id, IPC_RMID, NULL ); 
		    return NULL;
	}
	for ( p = (volatile SHM_CHANNEL *) ipc_id->shm, i = 1;
		i <= max_channel; i++, p = (volatile SHM_CHANNEL *) ((char *) p + size),
		p->status = IDLE );
	ipc_id->sem_id = create_sem ( ); 
	if ( ipc_id->sem_id == 0 ) 
		goto remove_shm;
	return ipc_id;
}

IPC * open_ipc ( int channel, int max_msg_size ) {
	IPC * ipc_id; int id, size;

	size = max_msg_size + sizeof (SHM_CHANNEL) - 1;
	id = shmget ( getuid ( ), 0 /*size * (channel + 1)*/, 0600 );
	if ( id == -1 ) return ( IPC *) 1;
	ipc_id = malloc ( sizeof ( IPC ) );
	if ( ipc_id == NULL ) return NULL;
	ipc_id->channel= channel;
	ipc_id->msg_id = id;
	ipc_id->server = 0;
	ipc_id->max_msg_size = max_msg_size;
	ipc_id->size = size;
	ipc_id->shm = shmat ( ipc_id->msg_id, NULL, SHM_RND );
	if ( ipc_id->shm == (void *) -1 ) return NULL;
	ipc_id->sem_id = create_sem ( );
	if ( ipc_id->sem_id == 0 )
		return NULL;
	return ipc_id;
}

int send_ipc ( IPC * ipc_id, void * data, int size, int channel ) {
	int chan_no; 
	volatile SHM_CHANNEL * p;

	chan_no = ipc_id->server ? channel : 1;
	p = (volatile SHM_CHANNEL *) (ipc_id->shm + chan_no * ipc_id->size);
	sem_lock ( ipc_id->sem_id );
	while ( p->status !=  IDLE ) ;
	p->size = size;
	p->chan_no = ipc_id->channel;
	memcpy ( (void *) p->msg, data, size );
	p->status = WRITTEN;
	sem_unlock ( ipc_id->sem_id );
	return IPC_SUCCESS;
}

int receive_ipc ( IPC * ipc_id, void * data ) {
	int chan_no; 
	volatile SHM_CHANNEL * p;

	chan_no = ipc_id->server ? 1 : ipc_id->channel;
	p = (volatile SHM_CHANNEL *) (ipc_id->shm + chan_no * ipc_id->size);
	while ( p->status != WRITTEN ) ;
	memcpy ( data, (void *) p->msg, p->size );
	p->status = IDLE;
	return ipc_id->server ? p->chan_no : IPC_SUCCESS;
}

void close_ipc ( IPC * ipc_id ) {
	FILE *fp;

	shmdt ( ipc_id->shm );
	if ( ipc_id->server ) 
	shmctl ( ipc_id->msg_id, IPC_RMID, NULL );
	rem_sem ( ipc_id->sem_id );
	free ( ipc_id );
	return;
}
