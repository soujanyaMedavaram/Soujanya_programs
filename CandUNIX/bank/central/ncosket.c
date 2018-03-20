# include <stdio.h>
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
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define SERV_TCP_PORT	6000
# define SERV_HOST_ADDR	"89.0.0.230"

struct ipc {
	int sock_fd;
	int server;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	IPC * ipc_id;
	struct sockaddr_in serv_addr;

/*	if ( !access ( "FIFO1", F_OK ) )
		return ( IPC * )1;  // server already started */
	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->server  = 1;
	ipc_id->sock_fd =  socket ( AF_INET, SOCK_STREAM, 0 );
	if ( ipc_id->sock_fd < 0 )
		return NULL;
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_addr.sin_port        = htons ( SERV_TCP_PORT );
	if ( bind ( ipc_id->sock_fd, (struct sockaddr *)&serv_addr , sizeof 
			  ( serv_addr ) ) < 0 )
		return NULL;
	listen ( ipc_id->sock_fd, 5 );
	return ipc_id;
}

IPC * open_ipc ( int channel, int max_msg_size ) {
	IPC * ipc_id;
	struct sockaddr_in ser_addr;

	/*if ( access ( "FIFO1", F_OK )  < 0 )
		return  ( IPC *) 1; */ // server not started.
	ipc_id = malloc ( sizeof ( IPC ) );
	ipc_id->server  = 0;
	ipc_id->sock_fd =  socket ( AF_INET, SOCK_STREAM, 0 );
	if ( ipc_id->sock_fd < 0 )
		return NULL;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr ( SERV_HOST_ADDR );
	ser_addr.sin_port = htons ( SERV_TCP_PORT );
	if ( connect ( ipc_id->sock_fd, ( struct sockaddr *)&ser_addr, 
				  sizeof ( ser_addr ) )	== -1 )
		return NULL;
	return ipc_id;
}

int send_ipc ( IPC * ipc_id, void * data, int size, int channel ) {
	struct iovec v[2]; int pos, fd;
	pos = 0;
	fd = ipc_id->server ? channel : ipc_id->sock_fd;
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
	int newsockfd, cli_len, fd , size ;
	struct sockaddr_in serv_addr, cli_addr;

	if ( ipc_id->server ) {
		cli_len = sizeof ( cli_addr );
		newsockfd = accept ( ipc_id->sock_fd, ( struct sockaddr *)&cli_addr,
							 &cli_len );
		if ( newsockfd < 0 ) return IPC_FAIL;
	}
	fd = ipc_id->server ? newsockfd : ipc_id->sock_fd;
	if ( read ( fd, & size, sizeof (int) ) != sizeof (int) )
		return IPC_FAIL;
	if ( read ( fd, data, size ) != size )
		return IPC_FAIL ;
	return ipc_id->server ? newsockfd : IPC_SUCCESS; 
}

void close_ipc ( IPC * ipc_id ) {
	close( ipc_id->sock_fd );
	free ( ipc_id );
}
