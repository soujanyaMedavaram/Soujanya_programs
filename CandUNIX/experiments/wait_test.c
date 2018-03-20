# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

void catch ( int sig ) { }

main ( ) {
	int w_exit, exit_code;
	
	printf ( "before signal exit_code = %d\n", exit_code );
	signal ( SIGCHLD, SIG_IGN );
	if ( fork ( ) == 0 ) {
		printf ( " child process\n" );
		exit ( 0 );
	}
	w_exit = wait ( &exit_code );
	printf ( "<%s>\n", strerror ( errno ) );
	printf ( " w_exit = %d exit_code = %d\n", w_exit, exit_code );
}

