# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>

main  ( ) {
	int sockfd, new_sockfd;
	struct sockaddr_in cli_addr, serv_addr;
	sockfd = socket ( PF_INET, SOCK_STREAM, 0 );
	printf ( "%d\n", sockfd );
	serv_addr.sin_family      = PF_INET;
	serv_addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	serv_addr.sin_port        = htons ( SERV_TCP_PORT );
	if ( bind ( sockfd, ( struct sockaddr *) &serv_addr, sizeof ( serv_addr ) ) < 0 )
		fprintf ( stderr, "server : can't bind local address\n" );
	listen ( sockfd, 5 );
	for ( ; ; ) {
		clilen = sizeof ( cli_addr );
		newsockfd = accept ( sockfd, ( struct sockaddr *) & cli_addr, &clilen );
		if ( newsockfd < 0 )
			fprintf ( stderr, "server : accept error \n" );
		if ( (childpid = fork ) < 0 )
			fprintf ( stderr, "fork failed \n" );
		else if ( childpid == 0 ) {
			close ( sockfd );
			printf ("process request \n" );
			exit ( 0 );
		}
		close ( newsockfd );
	}
}
	close ( sockfd );
}


