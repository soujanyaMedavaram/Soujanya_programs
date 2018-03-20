# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define MAXBYTES	500

# define SERV_UDP_PORT	6000

main  (  ) {
	int sockfd, size_client;
	struct sockaddr_in server, client;
	char buff[MAXBYTES];

	if ( (sockfd = socket ( AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		fprintf ( stderr, "Server: socket failed\n" );
		exit ( 1 );
	}
	bzero ( (char *)&server, sizeof ( server )  );
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl ( INADDR_ANY );
	server.sin_port = htons ( SERV_UDP_PORT );
	if ( bind ( sockfd,(struct sockaddr *)&server, sizeof ( server)) <0 ){
		fprintf ( stderr, " Server: bind failed\n" );
		exit ( 2  );
	}
	size_client = sizeof( client );
	if ( recvfrom ( sockfd, buff, MAXBYTES, 0, (struct sockaddr *)&client,
						&size_client ) < 0 ) {
		fprintf ( stderr, " recvfrom failed\n" );
		exit ( 3 );
	}
	printf ( "Msg rcvd <%s>\n", buff );
	printf ( " \n enter a line to send to client\n" );
	fgets ( buff, MAXBYTES, stdin );
	sendto ( sockfd, buff, strlen ( buff ) + 1, 0, (struct sockaddr *)&client,
				size_client );
	return 0;
}

