# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

main ( ) {
	int fd;
	switch ( fork ( ) ) {
		case -1:
				fprintf ( stderr, "fork failed \n" );
				exit ( 1 );
		default : break;
		case 0:
				fd = open ( "temp", O_RDONLY, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "open failed \n" );
					exit ( 2 );
				}
				close ( 0 );
				if ( dup ( fd ) != 0 ) {
					fprintf ( stderr, "dup failed\n" );
					exit ( 3 );
				}
				execl ( "/usr/bin/wc", "wc", NULL );
				fprintf ( stderr, "exec failed \n" );
				exit ( 4 );
	}wait ( NULL );
	exit ( 0 );
}
