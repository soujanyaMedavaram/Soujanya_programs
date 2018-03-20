# include <stdio.h>

main (int argc, char *argv[] ) {
	int c, pos, tab, rem , i;

	pos = 0;
	if ( argc == 2 )
		tab = atoi(argv[1]);
	else tab = 4;
/*	while ( ( c = getchar () ) != EOF ) {
		if ( ( rem = (pos % tab)) != 0  && c == '\t' )
			for ( i = rem; i < tab; i++ )
				putchar ( ' ' );
		else putchar ( c );
		pos++;
	}*/
	while ( (c = getchar()) != EOF ) {
		if ( c == '\t' ) {
			do {
				putchar (' ');
				pos++;
			} while ( pos % tab );
		}
		else { putchar (c);
			pos++;
		}
		if ( c == '\n' ) pos = 0;
	}
}
		

