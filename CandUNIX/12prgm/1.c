# include <stdio.h>

void dec_2_bin ( int );
main ( ) {
	int num,x;
	printf ( "\n enter a number \n" );
	scanf ( "%d", &num );
	dec_2_bin ( num );
}

void dec_2_bin ( int i ) {
	int andmask, k,j;
	for ( j = 31; j >= 0; j-- ){
		andmask = 1 << j;
		k = andmask & i;
		k == 0 ? putchar ( '0' ) : putchar ( '1' );
	}
	printf ( "\n" );
}
