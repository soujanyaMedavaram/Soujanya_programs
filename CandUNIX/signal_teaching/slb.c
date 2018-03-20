// sleep better file, to understand sleep, alarm and pause sys calls

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <setjmp.h>

void sig_catcher ( int sig );

main ( ) {
	signal ( SIGALRM, sig_catcher );
	alarm ( 5 );
	printf ( "Hai " ); fflush ( stdout );
	sleep ( 2 );
	printf ( "Sri\n" );
	pause ( );
}

void sig_catcher ( int sig ) {
	printf ( "got sig\n" );
}
