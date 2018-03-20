# include <stdio.h>
# include <stdlib.h>
main ( ) {
	char *s;
	s = malloc ( 20 );
	printf ( "\n enter a number \n" );
	scanf ( "%s",s );
	printf ( "\n %d->number \n", myatoi(s) );
	printf ( "\n %d->ascii\n", atoi ( s ) );
}
int myatoi ( char *s ) {
	int i, n;
	n =0;
	for ( i =0; s[i] >= '0' && s[i]  <= '9'; i++ )
		n = n*10 + (s[i] - '0' );
	return n;
}
