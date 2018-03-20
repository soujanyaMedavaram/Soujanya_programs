# include <stdio.h>

void change_comment ( FILE *fp ) {
	char line[100], *p;
	int lineno = 0, flag = 1;

	while ( (fgets ( line, 100, fp )) != NULL ) {
		lineno++;
		for ( p = line; isblank ( *p ); p++ );
		if ( *p != '/' ) {
			printf ( "%s", line );
			continue;
		}
		if ( *p == '/' ) { 
			p++; 
			if ( *p == '*' )
				flag = 1;
			else fprintf ( stderr, " Line%d:Syntax error at %c\n", lineno, *p );
		}
		if ( flag == 1 ) {
			printf ( "///" );
			while ( *p != '*' ) {
				if ( *p == '\n' ) printf ( "///" );
				p++;
				if ( *p == '*' ) p++;
				if ( *p == '/' ) break;
				p--;
				putchar ( *p );
			}
		}
	}
}
		

main ( int argc, char *argv[] )
{
	FILE *fp;

	if ( argc > 1 ) 
		while ( *++argv ) {
			if ( ( fp = fopen ( *argv, "r" ) ) == NULL ) {
				fprintf ( stderr, "%s- file not opened \n" , *argv );
				continue;
			}
			change_comment ( fp );
			fclose ( fp );
		}
	else if ( argc == 0 )
		change_comment ( stdin );
	exit ( 0 );
}


	

