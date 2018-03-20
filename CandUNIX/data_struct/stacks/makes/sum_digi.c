# include <stdio.h>

main ( ) {
	int num;
	scanf ( "%d", &num );
	num = sum ( num );
	printf ( "%d\n", num );
}

int sum ( int num ) {
 static int sum_num = 0;
 if ( num != 0 ) {
 	sum_num += num % 10;
	printf ( "%d->sum_sub\n", sum_num );
	sum ( num / 10 );
printf ( "%d->num\n", num );
}
	return sum_num;
}
