# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main ( ) {
	int *src ;
	int i , j = 0;
	src = malloc ( 5 * sizeof ( int ) );
	for ( i =0; i < 5; i++ )
		src[i] = j++;
	int *dst = malloc ( sizeof ( src ) );
//	memcpy ( dst, src, 5 * sizeof ( int ) );
	memcpy ( dst, src, 500 );
	for ( i =0; i < 5 ; i++ )
		printf ( "%d\n", dst[i] );
}
