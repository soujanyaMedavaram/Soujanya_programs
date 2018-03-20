# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../ipc.h"
# include "../../request_reply.h"
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>

# define CH_MAX	100

struct ipc {
	int *fd;
};

IPC * open_ipc ( int curr_chl ) {
	char channel[CH_MAX];

	IPC *ipc_id;
	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->fd = malloc ( 2 * sizeof ( int ) );
	ipc_id->fd[0] = open ( "FIFO0", O_WRONLY );
	if ( ipc_id->fd[0] < 0 ) 
		return NULL;
	sprintf ( channel, "FIFO%d", curr_chl );
	ipc_id->fd[1] = open ( channel, O_RDWR );
	if ( ipc_id->fd[1] < 0 )
		return NULL;
	return ipc_id;
}

IPC * create_ipc ( int max_chl ) {
	int i, j;
	char channel[CH_MAX];
	IPC *ipc_id;

	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->fd = malloc ( (max_chl + 1 ) * sizeof ( int ) );
	for ( i = 0; i <= max_chl; i++ ) {
		sprintf ( channel, "FIFO%d", i );
		if ( mkfifo ( channel, 0600 ) < 0 && EEXIST != errno ) {
			for ( j = 0; j < i; j++ ) {
				sprintf ( channel, "FIFO%d", j );
				close ( ipc_id->fd[j] );
				unlink  ( channel );
			}
			return NULL;
		}
		ipc_id->fd[i] = open ( channel, O_RDWR );
		if ( ipc_id->fd[i] < 0 ) {
			for ( j = 0; j < i; j++ ) {
				close ( ipc_id->fd[j] );
				sprintf ( channel, "FIFO%d", j );
				unlink ( channel );
			}
			return NULL;
		}
	}
	return ipc_id;
}

int read_request ( IPC *ipc_id, void *req, int size ) {
	if ( read ( ipc_id->fd[0], req, size ) != size )
		return IPC_FAIL ;
	return IPC_SUCCESS;
}

int write_request ( IPC *ipc_id, void *req, int size ) {
	if ( write ( ipc_id->fd[0], req, size ) != size ) 
		return IPC_FAIL;
	return IPC_SUCCESS;
}

int write_reply ( IPC *ipc_id, void *rep,  int size, int channel) {
	if ( write ( ipc_id->fd[channel], rep, size ) != size ) 
		return IPC_FAIL;
	return IPC_SUCCESS;
}

int read_reply ( IPC *ipc_id, void *rep, int size ) {
	if ( read ( ipc_id->fd[1], rep, size ) != size )
		return IPC_FAIL;
	return IPC_SUCCESS;
}

void remove_ipc ( IPC *ipc_id, int fd_max ,int fd_db ) {
	int i;
	char channel[CH_MAX];
	close ( fd_db );
	for ( i = 0; i <= fd_max; i++ ) {
		close ( ipc_id->fd[i] );
		unlink ( channel );
	}
	free ( ipc_id->fd );
	free ( ipc_id );
}

void close_client ( IPC *ipc_id, int curr_chl ) {
	close ( ipc_id->fd[0] );
	close ( ipc_id->fd[curr_chl] );
}
