# include <stdio.h>
# include <stdarg.h>

int vadd ( int  nint,... )  {
	va_list va;
	int total;
	va_start ( va, nint );
	total = 0;
	while ( nint-- ) total += va_arg ( va, int );
	va_end ( va ); 
	return total;
}
main  ( ) {
	printf ( "%d\n", vadd ( 0 ) );
	printf ( "%d\n", vadd ( 1, 10 ) );
	printf ( "%d\n", vadd ( 4, 10, 20, 30, 40, 50 ) );
}
