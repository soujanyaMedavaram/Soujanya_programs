# include <stdio.h>

int func ( int x ) {
	if ( x <= 0 ) return 1;
	return x * func ( x - 1 );
}

main () {
	int var;
	var = func ( 6 );
	printf ( "\n var -> %d\n", var );
}
