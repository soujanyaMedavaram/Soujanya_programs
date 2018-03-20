# include <stdio.h>

main ( ) {
	FILE *fp;
	char *buf;
	fp = fopen ( "100kb.data", "r" );
	while ( fread ( buf, 1, 1, fp ) != 0 );
}
