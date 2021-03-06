# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define SERV_TCP_PORT	5111
# define SERV_HOST_ADDR	"89.0.0.230"

main ( int argc, char *argv[] ) {
	int sockfd, namelen, namefd;;
	char * buf;

	buf = malloc ( 100 );
	strcpy ( buf, argv[1] );
	struct sockaddr_in ser_addr;
	sockfd = socket ( AF_INET, SOCK_STREAM, 0 );
	if ( sockfd < 0 ) {
		fprintf ( stderr, "Socket failed \n" );
		exit ( 1 );
	}
	printf ( "%d-> IN clinet \n" , sockfd );
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr ( SERV_HOST_ADDR );
	ser_addr.sin_port = htons ( SERV_TCP_PORT );
	connect ( sockfd, ( struct sockaddr *)&ser_addr, sizeof ( ser_addr ) );
	write ( sockfd, buf, strlen(buf) + 1 );
	read ( sockfd, buf, 100 );
	printf ( "Server msg  = <%s>\n", buf );
	printf ( " IN CLIENT: %s\n", argv[1] );
}
	
