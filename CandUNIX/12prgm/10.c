# include <stdio.h>

int count_1 ( int );
main ( ) {
	int num;
	printf ( "\n enter a number \n" );
	scanf ( "%d", &num );
	num = count_1(num );
	printf ( "\n Number of  ones %d\n", num ); 
}

int count_1 ( int num ) {
	int no1;
	for ( no1 = 0; num != 0; num >>= 1 ) 
		if ( num & 01 )
			no1++;
	return no1;
}
