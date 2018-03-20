# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define MAXBYTES	500

# define SERV_UDP_PORT 	 6000
# define SERV_HOST_ADDR  "89.0.0.230"

main  (  ) {
	int sockfd, size_server;
	struct sockaddr_in server, client;
	char buff[MAXBYTES];

	if ( (sockfd = socket ( AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		fprintf ( stderr, "client: socket failed\n" );
		exit ( 1 );
	}
	bzero ( (char *)&client, sizeof ( client )  );
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr ( SERV_HOST_ADDR );
	server.sin_port = htons ( SERV_UDP_PORT );
	if ( bind ( sockfd,(struct sockaddr *)&client, sizeof ( client)) <0 ){
		fprintf ( stderr, " Client: bind failed\n" );
		exit ( 2  );
	}
	size_server = sizeof( server );
	printf ( " \n enter a line to send to client\n" );
	fgets ( buff, MAXBYTES, stdin );
	sendto ( sockfd, buff, strlen ( buff ) + 1, 0, (struct sockaddr *)&server,
				size_server );

	if ( recvfrom ( sockfd, buff, MAXBYTES, 0, (struct sockaddr *)&server,
						&size_server ) < 0 ) {
		fprintf ( stderr, " recvfrom failed\n" );
		exit ( 3 );
	}
	printf ( "<%s>\n", buff );
	return 0;
}

