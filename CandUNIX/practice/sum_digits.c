# include <stdio.h>
main ( ) {
	int num;

	printf ( "\n enter anumber \n" );
	scanf ( "%d", &num );
	printf ( "sum = %d\n", sum_digi( num ));
}

int sum_digi ( int num ) {
	static int sum = 0;
	if ( num > 0 ){
		sum += num % 10;
		sum_digi(num/10);
	}
	return sum;
}
