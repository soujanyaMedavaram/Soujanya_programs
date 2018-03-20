# include <stdio.h>

main ( ) {
	int i = 3, j;
	foo (&i);
	printf ("%d\n", i );
}

foo ( int *i ) {
	i = 10;
}
