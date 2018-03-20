# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define SERV_TCP_PORT	5111

main  ( ) {
	int sockfd, clilen, newsockfd, filefd;
	struct sockaddr_in serv_addr, cli_addr;
	char *buf, c ;

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
	listen ( sockfd, 5 );
	clilen = sizeof ( cli_addr );
	newsockfd = accept ( sockfd, (struct sockaddr *)&cli_addr, &clilen ); 
	printf ( "\n after accept \n" );
	printf ( "%d->in server \n" , newsockfd );
	if ( newsockfd < 0 ) {
		fprintf ( stderr, " accept failed \n" );
		exit ( 2 );
	}
	read ( newsockfd, buf, 20 );
	//strcpy ( buf, "Hai" );
	printf ( "The filename  = <%s>\n", buf );
	if ( (filefd = open ( buf, O_RDONLY )) == -1 ) {
		strcpy ( buf, "Permission denied" );
		write ( newsockfd, buf, strlen(buf) + 1 );
	}
	else {
		while ( read ( filefd, &c, 1 ) != -1 )
			write ( newsockfd, &c, 1 );
	}
	close ( newsockfd );
	close ( sockfd );
}
