# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main ( ) {
	int fd;

	switch ( fork ( ) ) {
		case -1: fprintf ( stderr, " fork failed \n" );
				 break;
		case 0: 
				fd = open ( "temp", O_CREAT | O_TRUNC | O_WRONLY, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "open failed\n" );
					exit ( 2 );
				}
				close ( 1 );
				if ( dup ( fd ) != 1 ) {
					fprintf ( stderr, "dup failed \n" );
					exit ( 3 );
				}
				close ( fd );
				execl ( "/bin/ls", "ls","-l", NULL );
				fprintf ( stderr, "exec failed \n" );
				exit ( 4 );
	} wait ( NULL ); exit ( 0 );
}
