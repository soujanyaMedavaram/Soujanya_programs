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
				execl ( "/bin/ls", "ls","-l", NULL );
				fprintf ( stderr, "exec failed \n" );
				exit ( 4 );
	}  exit ( 0 );
}
