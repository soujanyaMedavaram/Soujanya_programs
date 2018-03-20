//# include <iostream>
# include <stdio.h>
# include <signal.h>

//using namespace std;

void catch ( int sig ) {
	printf ( "signal handler\n" );
}
main ( ) {
	signal ( SIGSEGV, catch );
	printf ( "Hai\n" );
}
