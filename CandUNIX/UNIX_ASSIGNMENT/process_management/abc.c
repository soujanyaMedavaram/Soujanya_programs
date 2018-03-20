# include <stdio.h>

main ( int argc, char ** argv ) {
	printf ( "Hello\n" );
	fprintf ( stderr, "No Hello\n" );
	printf ( "Args : %s  ", argv[0] );
	if ( argc > 1 )
		printf ( "%s  ", argv[1] );
	if ( argc > 2 )
		 printf ( "%s\n", argv[2] );
	else putchar ( '\n' );
}
