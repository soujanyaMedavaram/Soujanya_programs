# include <stdio.h>
# include <stdlib.h>

void str_rev ( char * );
main ( ) {
	char *name;
	name = malloc ( 20 );
	printf ( "\n enter a string\n" );
	scanf ( "%s", &name );
	str_rev ( name );
}

	static int i = strlen ( name ) - 1;
void str_rev ( char * name ) {
	if ( i != 0 ) {
		putchar ( name[i] );
		i--;
		strrev ( name );
	}
}

