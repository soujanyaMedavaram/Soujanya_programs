# include <stdio.h>

main ( ) {
	int i = 8;
	int j = 2;
	int k = (i & j) + (i && j) + ( i ^ j );
	printf ( "%d\n", k );
}
