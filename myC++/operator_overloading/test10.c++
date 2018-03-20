# include <iostream>
# include <signal.h>

using namespace std;

void katch ( int sig ) {
	cout <<  "signal handler\n" ;
}
main ( ) {
	signal ( SIGSEGV, katch );
	cout << "Hai\n" ;
}
