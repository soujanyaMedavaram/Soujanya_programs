# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

main ( ) {
	int fd_r, fd_w;
	mkfifo ( "serfifo", O_CREAT | 0600 );
	switch ( fork ( ) ) {
		case -1:
		case 0: break;
		default: exit ( 0 );
	}
	fd_r = open ( "serfifo", O_RDONLY );
	printf ( "hai\n" );
	close ( 1 );
	close ( 2 );
	close (  3 );
}

