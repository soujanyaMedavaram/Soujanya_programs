# include <stdio.h>
int odd_evev ( int );
main ( ) {
	int num;
	printf ( "\n enter a number\n" );
	scanf ( "%d", &num );
	num = odd_even ( num );
	if ( num == 0 ) 
		printf ( "\n geiven number is even\n" );
	else if ( num == 1 ) 
		printf ( "\n given number is odd \n" );
}

int odd_even ( int num ) {
/*	int andmask;
	andmask = num & 1;
	return andmask; */
	return num & 1;
}
