# include <stdio.h>

void showbits ( int );
int set_n_bit ( int, int );

main ( ) {
	int num, nth;

	printf ( "Enter a number \n" );
	scanf ( "%d", &num );
	printf ( "Enter nth bit \n" );
	scanf ( "%d", &nth );
	showbits ( num );
	num = set_n_bit ( num , nth);
	showbits ( num );
}

void showbits ( int num ) {
	int andmask, j, k;

	for ( j = 31; j >= 0; j-- ){
/*		andmask = 1 << j;
		k = andmask & num;
		k == 0 ? putchar ( '0' ) : putchar ( '1' );*/
		putchar ( num & (1 << j) ? '1' : '0' );
	}
	printf ( "\n" );
}

int set_n_bit ( int num , int nth) {
	if ( !(num & 1 << nth) )
		num |= 1 << nth ;
	return num;
}
	
	
