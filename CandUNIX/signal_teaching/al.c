// program to understand alarm

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <setjmp.h>

void got_alarm ( int );

jmp_buf get_y;

main ( ) {
	int x = 1234, y = 4321;

	alarm ( 5 );
	signal ( SIGALRM, got_alarm );
	if ( setjmp ( get_y ) == 0 ) {
		printf ( "Enter x (within 5 sec):" );
		scanf ( "%d", & x );
	} else {
		printf ( "Enter y : " );
		scanf ( "%d", & y );
	}
	alarm ( 0 );
	printf ( "x = %d  y = %d\n", x, y );
}

void got_alarm ( int signo ) {
	printf ( "Got signal %d\n", signo );
	longjmp ( get_y, 1 );
}
