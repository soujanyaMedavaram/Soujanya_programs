# include <stdio.h>

void print_file ( FILE *fp );
main ( int argc, char *argv[] ) {
	FILE *fp;
	if ( argc == 1 ) { 
		fp = fopen ( "/etc/passwd",  "r" );
		print_file ( fp );
		fclose ( fp );
	}
	else while ( *++argv ) {
		fp = fopen ( *argv, "r" );
		printf ( "\n file -> %s\n", *argv );
		print_file ( fp );
		fclose ( fp );
	}
	exit ( 0 );
}

void print_file ( FILE *fp ) {
	char *data;
	long beg;
	int c;
	
	beg = ftell ( fp );
	fseek ( fp, 0, SEEK_END );
	while ( beg != ftell ( fp ) ) {
		fseek ( fp, -1, SEEK_CUR );
		c = getc ( fp );
		putchar ( c );
		fseek ( fp, -1, SEEK_CUR );
	}
}
	


