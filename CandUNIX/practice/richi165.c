# include <stdio.h>
# include <stdlib.h>
char *myfgets ( char *s, int n, FILE *iop ) {
	register int c;
	register char *cs;

	cs = s;
	while ( --n > 0 && (c = getc(iop)) != EOF )
		if ( ( *cs++ = c) == '\n' )
			break;
	*cs = '\0';
	printf ( "%d- c \n", c );
	return ( c= EOF && cs == s ) ? NULL : s;
}
	
main () {
	char *s;
	char *l;

	s = malloc ( 50 );
	l = myfgets ( s, 50, stdin );
	printf ( "s -> %s\n",s);
	printf ( "l -> %s\n",l);
}



