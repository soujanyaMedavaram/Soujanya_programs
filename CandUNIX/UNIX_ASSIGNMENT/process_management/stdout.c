# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main ( ) {
	int fd;

	fd = open ( "/dev/tty", O_WRONLY, 0600 );
	close ( 1 );
	if ( dup(fd) != 1 ) exit ( 1 );
	printf ( "Hello\n" );
}
