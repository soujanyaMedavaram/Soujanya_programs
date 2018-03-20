# include <stdio.h>

int power ( int base, int n ) {
	int i, p;

	p = 1;
	for ( i = 1; i <=n; ++i )
		p = p * base;
	return p;
}
main ( ) {
	int i;

	for ( i = 0; i < 10; ++ i )
		printf ( "%2d %4d %6d\n", i, power(2, i ), power (-3, i ) );
	return 0;
}

