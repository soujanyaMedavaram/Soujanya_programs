# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define SERV_TCP_PORT	5111

main  ( ) {
	int sockfd, clilen, newsockfd;
	struct sockaddr_in serv_addr, cli_addr;
	char *buf;

	buf = malloc ( 100 );
	switch ( fork ( ) ) {
		case -1 :
			fprintf ( stderr, "\n fork failed \n" );
			exit ( 1  );
		case 0: break;
		default : exit ( 0 );
	}
	buf = malloc ( 20 );
	sockfd = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( sockfd < 0 ) {
		fprintf ( stderr, "socket failed\n" );
		exit ( 1 );
	}
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_addr.sin_port        = htons ( SERV_TCP_PORT );
	if ( bind ( sockfd, ( struct sockaddr *)&serv_addr, sizeof ( serv_addr ) ) < 0 ) {
		fprintf ( stderr, "bind failed \n" );
		exit ( 2 );
	}
	printf ( "Before Listen\n" );
	listen ( sockfd, 5 );
	clilen = sizeof ( cli_addr );
	printf ("after listen\n");
	newsockfd = accept ( sockfd, (struct sockaddr *)&cli_addr, &clilen ); 
	printf ( "\n after accept \n" );
	printf ( "%d->in server \n" , newsockfd );
	if ( newsockfd < 0 ) {
		fprintf ( stderr, " accept failed \n" );
		exit ( 2 );
	}
	read ( newsockfd, buf, 20 );
	strcpy ( buf, "Hai" );
	write ( newsockfd, buf, strlen(buf) + 1 );
	printf ( " IN SERVER: %s\n", buf );
	close ( newsockfd );
	close ( sockfd );
}
