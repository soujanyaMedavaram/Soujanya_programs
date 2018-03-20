# include <stdio.h>
# include <errno.h>

main ( ) {
	int pfd[2];

	if ( pipe(pfd) < 0 ) {
		fprintf ( stderr, "pipe failed \n" );
		exit ( 2 );
	}
	switch ( fork ( ) ) {
		case -1: 
			fprintf ( stderr, "\n fork failed \n" );
			exit ( 1 );
		case 0:
			close ( 1 );
			close ( pfd[0] );
			if ( (dup (pfd[1])) != 1 ) {
				fprintf ( stderr, "\n dup failed \n" );
				exit ( 3 );
			}
			close ( pfd[1] );
			execlp ( "ls","ls", "-l",NULL);
			fprintf ( stderr, "can not exec \n" );
			exit ( 4 );
		default :
			wait ( 0 );	
	}
	switch ( fork ( ) ) {
		case -1 : 
			fprintf ( stderr, "fork failed \n" );
			exit ( 5 );
		case 0:
			close ( 0 );
			close ( pfd[1] );
			if (dup (pfd[0]) != 0 ) {
				fprintf ( stderr, "wc -dup failed \n" );
				exit ( 6 );
			}
			close ( pfd[0] );
			execlp ( "wc","wc",NULL );
			fprintf ( stderr, "cannot exec\n" );
			exit ( 7 );
		default :
			break;
	}
	close ( pfd[0] );
	close ( pfd[1] );
	wait ( 0 );
	exit ( 0 );
}
