# include <stdio.h>

main ( ) {
	FILE *fp;
	int i;
	fp =fopen ( "hai", "w" );
	for ( i = 0; i <512; i++ )
		fprintf ( fp, "%d", i );
}
