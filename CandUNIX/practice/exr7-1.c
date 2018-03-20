# include <stdio.h>
# include <string.h>

main ( int argc, char * argv[] ) {
	int c;
	if ( argc == 2 )
	{
		if ( !strcmp ( argv[1], "lower") )
			while ( ( c = getchar() ) != EOF )
				putchar ( tolower ( c ) );
		else if ( ! strcmp ( argv[1], "upper" ) )
			while ( ( c = getchar () ) != EOF )
				putchar ( toupper ( c ) );
		else {
			fprintf ( stderr, "wrong option - %s\n", argv[1] );
			exit ( 1 );
	  }
	}
	else 
		fprintf ( stderr, "Usage: <a.out> <lower> or <upper>\n " );
	exit ( 0 );
}
