# include <stdio.h>

main ( ) {
	int num;
	printf ( "\n enter a number \n") ;
	scanf ( "%d", &num );
	num = num >> 2 ;
	printf ( "%d", num );
}
