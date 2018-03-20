# include <stdio.h>

# define max(a,b)	(a > b ? a : b)

void sub1 ( ) {
	printf ( "hai" );
}
main ( ) {
	int x;
	x = max ( 10, 20 );
	printf ( "%d\n", x );
	sub1 ( );
}
