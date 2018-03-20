# include <stdio.h>
//# include <sys/time.h>
//# include <sys/select.h>
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

# define SERV_TCP_PORT	6000
# define SERV_HOST_ADDR	"89.0.0.230"

int fd;
void sig_action ( int signo, siginfo_t *info, void *old );

struct ipc {
	int * sock_fd;
	int server;
	int nfd;
};

IPC * create_ipc ( int max_channel, int max_msg_size ) {
	IPC * ipc_id;
	struct sockaddr_in serv_addr;
	int flags;
	struct sigaction sig_act;

	printf ( "USER %d  KERNEL %d  TIMER %d  MESGQ %d  SIGIO %d  ASYNCIO %d\n",
			SI_USER, SI_KERNEL, SI_TIMER, SI_MESGQ, SI_SIGIO, SI_ASYNCIO );
	printf ( "IN %d  OUT %d  MSG %d  ERR %d  PRI %d\n",
			POLL_IN, POLL_OUT, POLL_MSG, POLL_ERR, POLL_PRI );
	//printf ( "%d->F_SETSIG\n", F_SETSIG );
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
	fcntl ( ipc_id->sock_fd[0], F_SETOWN, getpid( ) );
//	fcntl ( ipc_id->sock_fd[0], F_SETSIG, SIGIO );
	flags = fcntl ( ipc_id->sock_fd[0], F_GETFL );
	fcntl ( ipc_id->sock_fd[0], F_SETFL, flags | O_ASYNC );
	memset ( & sig_act, 0, sizeof (sig_act) );
	sig_act.sa_sigaction = sig_action;
	sig_act.sa_flags     = SA_SIGINFO;
	sigaction ( SIGPOLL, &sig_act, NULL );
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

void sig_action ( int signo, siginfo_t *info, void *old ) { 
	printf ( "In signal %d  handler\n", signo );
	fd = info->si_fd;
	printf ( "fd %d  code %d  signo %d  errno %d  pid %d  uid %d\n",
		fd, info->si_code, info->si_signo, info->si_errno, info->si_pid,
			info->si_uid );
		printf ( "\n END SIGNAL HANDLER\n" );
}

int receive_ipc ( IPC * ipc_id, void * data ) {
	int cli_len, size , newsockfd, i, fd_sig;
	struct sockaddr_in cli_addr;
	int flags;

	while ( 1 ) {
		printf ( "%6s: In receive\n", ipc_id->server ? "Server" : "Client" );
		pause ( );
		printf ( "\n after pause\n" );
		printf ( "ipc_id->server %d , fd %d ipc_id->sockfd[0] %d\n" ,
					ipc_id->server, fd, ipc_id->sock_fd[0] );
		if ( !ipc_id->server || fd != ipc_id->sock_fd[0] ) break;
		cli_len = sizeof ( cli_addr );
		printf ( "\n before accept\n" );
		newsockfd = accept ( fd, (struct sockaddr *) &cli_addr, &cli_len );
		if ( newsockfd < 0 ) 
			return IPC_FAIL;
		printf ( "after accepet:%d \n" ,newsockfd );
		ipc_id->sock_fd = realloc ( ipc_id->sock_fd,
					(ipc_id->nfd + 1 ) * sizeof ( int ) );
		ipc_id->sock_fd[ipc_id->nfd++] = newsockfd;
		fcntl ( newsockfd, F_SETOWN , getpid( ) );
//		fcntl ( newsockfd, F_SETSIG , SIGIO );
		flags = fcntl ( newsockfd, F_GETFL );
		fcntl ( newsockfd, F_SETFL, flags | O_ASYNC );
	}
	if ( read ( fd, & size, sizeof (int) ) != sizeof ( int ) )
		return IPC_FAIL;
	if ( read ( fd, data, size ) != size )
		return IPC_FAIL;
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
