// this is to create 100Kb file.

# include <stdio.h>

main ( ) {
	FILE *fp;
	int i;
	fp = fopen ( "100kb.data", "w" );
	for ( i = 0; i < 102400; i++ )
		putc ( i, fp );
	fclose ( fp );
}
