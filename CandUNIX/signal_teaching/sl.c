// program to understand pause() system call

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <setjmp.h>

jmp_buf waiting;

void sig_handler ( int sig );

main ( ) {
	signal ( SIGALRM, sig_handler );
	alarm ( 2 );
	if ( setjmp ( waiting ) == 0 ) {
		pause ( );
	}
}

void sig_handler ( int sig ) {
	longjmp ( waiting, 1 );
}
