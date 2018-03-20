# include <stdio.h>
main ( ) {
	long x;
	x = rand ();
	printf ( "1->%ld\n", x);
	srand( 10 );
	x = rand ( );
	printf ( "2->%ld", x);
}

