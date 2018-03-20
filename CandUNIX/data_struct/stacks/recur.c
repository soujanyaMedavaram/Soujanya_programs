# include <stdio.h>
main ( ) {
	sub1 ( );
}
int sub1 ( ) {
	static int i =0;
	while ( i < 10 ) {
		i++;
		printf ( "%d ", i );
	}
}
