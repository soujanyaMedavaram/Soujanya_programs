# include <stdio.h>

int vadd ( int  nint,... )  {
	char *va_list;
	int total = 0;

	va_list = (char *)(&nint + 1 );
	for ( total = 0; nint > 0; ) {
		total += *(int *)va_list;
		va_list += sizeof ( int );
		nint--;
	}
	return total;
}
main  ( ) {
	printf ( "%d\n", vadd ( 0 ) );
	printf ( "%d\n", vadd ( 1, 10 ) );
	printf ( "%d\n", vadd ( 4, 10, 20, 30, 40, 50 ) );
}
