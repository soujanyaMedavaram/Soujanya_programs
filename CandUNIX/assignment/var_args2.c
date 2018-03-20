# include <stdio.h>

int vadd ( int  nint,... )  {
	char *va_list;
	int total ;

	va_list = (char *)(&nint + 1 );
	total = 0;
	while ( nint-- )
		total += ( (int*)va_list += 1)[-1];
	return total;
}
main  ( ) {
	printf ( "%d\n", vadd ( 0 ) );
	printf ( "%d\n", vadd ( 1, 10 ) );
	printf ( "%d\n", vadd ( 4, 10, 20, 30, 40, 50 ) );
}
