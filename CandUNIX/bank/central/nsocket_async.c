# include <stdio.h>
# include <sys/time.h>
# include <sys/select.h>
# include <sys/uio.h>
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
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define SERV_TCP_PORT	5000
# define SERV_HOST_ADDR	"89.0.0.230"

struct ipc {
	int * sock_fd;
	int server;
	int nfd;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	IPC * ipc_id;
	struct sockaddr_in serv_addr;

	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->server  = 1;
	ipc_id->nfd = 1;
	ipc_id->sock_fd = malloc ( sizeof( int ) );
	ipc_id->sock_fd[0] = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( ipc_id->sock_fd[0] < 0 )
		return NULL;
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_addr.sin_port        = htons ( SERV_TCP_PORT );
	if ( bind ( ipc_id->sock_fd[0],
			(struct sockaddr *)&serv_addr , sizeof ( serv_addr ) ) < 0 ) {
		free ( ipc_id->sock_fd );
		free ( ipc_id );
		return (IPC *) 1;
	}
	listen ( ipc_id->sock_fd[0], 5 );
	return ipc_id;
}

IPC * open_ipc ( int channel, int max_msg_size ) {
	IPC * ipc_id;
	struct sockaddr_in ser_addr;

	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->server  = 0;
	ipc_id->sock_fd  = malloc ( sizeof ( int ) );
	ipc_id->sock_fd[0] = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( ipc_id->sock_fd[0] < 0 ) {
		free ( ipc_id->sock_fd );
		free ( ipc_id );
		return NULL;
	}
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr ( SERV_HOST_ADDR );
	ser_addr.sin_port = htons ( SERV_TCP_PORT );
	if ( connect ( ipc_id->sock_fd[0],
			( struct sockaddr *)&ser_addr, sizeof ( ser_addr ) ) == -1 )
		return (IPC *) 1;
	return ipc_id;
}

int send_ipc ( IPC * ipc_id, void * data, int size, int channel ) {
	struct iovec v[2]; int pos, fd;

	pos = 0;
	fd = ipc_id->server ? channel : ipc_id->sock_fd[0];
	v[pos].iov_base = (char *) & size;
	v[pos++].iov_len  = sizeof (size);
	v[pos].iov_base = data;
	v[pos++].iov_len  = size;
	if ( writev ( fd, v, pos ) == -1 )
		return IPC_FAIL;
//	sleep ( 2 );
	return IPC_SUCCESS;
}

int receive_ipc ( IPC * ipc_id, void * data ) {
	int cli_len, fd , size , newsockfd, i, max, flags;
	struct sockaddr_in cli_addr;
	fd_set fd_list;

	i = 0;
	if ( ipc_id->server ) {
		while ( 1 ) {
			FD_ZERO ( &fd_list );
			for ( max = 0, i = 0; i < ipc_id->nfd; i++ ) {
				FD_SET  ( ipc_id->sock_fd[i], &fd_list );
				if ( max < ipc_id->sock_fd[i] )
					max = ipc_id->sock_fd[i];
			}
			select ( max + 1, &fd_list, NULL, NULL, NULL );
			for ( i = 0; i < ipc_id->nfd; i++ ) {
				if ( !FD_ISSET ( ipc_id->sock_fd[i], &fd_list ) ) continue;
				if ( i ) break;
				cli_len = sizeof ( cli_addr );
				newsockfd = accept ( ipc_id->sock_fd[0], 
						    	(struct sockaddr *)&cli_addr, &cli_len );
				if ( newsockfd < 0 ) 
					return IPC_FAIL;
				ipc_id->sock_fd = realloc ( ipc_id->sock_fd,
							(ipc_id->nfd + 1 ) * sizeof ( int ) );
				ipc_id->sock_fd[ipc_id->nfd++] = newsockfd;
				fcntl ( newsockfd, F_SETOWN, getpid ( ) );
				flags = fcntl ( newsockfd, F_GETFL );
				fcntl ( newsockfd, F_SETFL, falgs | O_ASYNC );
			}
			if ( i < ipc_id->nfd && i != 0)
				break;
		}
	}
	fd = ipc_id->sock_fd[i] ;
	if ( read ( fd, & size, sizeof (int) ) != sizeof (int) ) 
		return IPC_FAIL;
	if (  read ( fd, data, size ) != size )
		return IPC_FAIL ;
	return ipc_id->server ? fd : IPC_SUCCESS;
}

void close_ipc ( IPC * ipc_id ) {
	int i;

    if ( ipc_id->server ) {
		for ( i = 0; i < ipc_id->nfd; i++ )
			close( ipc_id->sock_fd[i] );
	} else close ( ipc_id->sock_fd[0] );	
	free ( ipc_id->sock_fd );
	free ( ipc_id );
}

int server_client ( IPC *ipc_id, int fd, int action ) {
	int i, j;

	switch ( action ) {
		case START :
			return IPC_SUCCESS;
		case ADD :
			return IPC_SUCCESS;
		case REM :
			for ( i = 0; i < ipc_id->nfd; i++ ) 
				if ( fd == ipc_id->sock_fd[i] ) 
					break;
			for ( j = i; j < ipc_id->nfd - 1; j++ )
				ipc_id->sock_fd[j] = ipc_id->sock_fd[j + 1];
			ipc_id->nfd--;
			return IPC_SUCCESS;
	}
}
