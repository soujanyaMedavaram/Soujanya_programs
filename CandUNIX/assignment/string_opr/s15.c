# include <stdio.h>
# include <stdlib.h>

void insert_string ( char *dst, char *src, int pos ) {
	char *scratch;
	int i, j;

//	scratch = malloc ( 40 );
	scratch = malloc ( strlen(dst) - pos + 1 );

	for ( i = pos, j = 0; i < strlen ( dst ); i++, j++ )
		scratch[j] = dst[i];
	scratch[j] = '\0';
	for ( i = pos, j = 0; j < strlen ( src ); i++, j++ )
		dst[i] = src[j];
	dst[i] = '\0';
	strcat ( dst, scratch );
	free (scratch );
}

main ( ) {
	char dst[50], src[25];
	int i = 0, pos, c;

	printf ( "\n enter the main string\n" );
	while ( ( c = getchar () ) != EOF && c!= '\n' )
		dst[i++] = c;
	dst[i] = '\0';
	printf ( "\n enter the string to be stuffed \n" );
	scanf ( "%s",src );
	printf ( "\n enter the position \n" );
	scanf ( "%d", &pos );
	insert_string ( dst, src, --pos );
	printf ( "\n the string after stuffing \n %s \n", dst );
	return 0 ;
}
