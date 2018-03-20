# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

main ( ) {
	FILE *fp;
	long lo;
	fp = fopen ( "2g_file.c", "w" );
	if ( fp == NULL ) 
		fprintf ( stderr, "open failed\n" );
	lo = (2 * 1000000 ) - 1;
	printf ( "%ld\n", lo );
	fseek ( fp, lo, SEEK_SET );
	fprintf ( fp, "hai this is uttara\n" );
	fclose ( fp );
}

