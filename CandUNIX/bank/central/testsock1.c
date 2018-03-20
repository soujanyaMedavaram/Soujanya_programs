# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>		// generic interface for networking
# include <netinet/in.h>		// specific structures used in internet (TCP/IP)
# define SERV_TCP_PORT	6000
//# include <arpa/inet.h>

main  ( ) {
	int sockfd, newsockfd, clilen;
	struct sockaddr_in cli_addr, serv_addr;

	sockfd = socket ( PF_INET, SOCK_STREAM, 0 );
	if ( sockfd < 0 ) {
		fprintf ( stderr, "socket failed \n" );
		exit ( 1  );
	}
	printf ( "%d->sockfd\n", sockfd );
	serv_addr.sin_family      = PF_INET;
	serv_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_addr.sin_port        = htons ( SERV_TCP_PORT );
	bind ( sockfd, ( struct sockaddr *) &serv_addr, sizeof ( serv_addr ) );
	listen ( sockfd, 5 );
	switch ( fork ( ) ) {
		case -1 :
			fprintf ( stderr, "fork failed \n" );
			exit ( 2 );
		case 0:
			printf ( "\n i child process \n" );
			clilen = sizeof ( cli_addr );
			newsockfd = accept ( sockfd, ( struct sockaddr *)&cli_addr, &clilen );
			printf ( "%d->new sokfd \n", newsockfd );
			close ( newsockfd );
		default :
			wait ( 0 );
			break;
	}
}


