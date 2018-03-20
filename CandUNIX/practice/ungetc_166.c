# include <stdio.h>
main () {
	int c;

	c = getchar ();
	while ( (c= getc (stdin )) != EOF )
		putchar ( c);
	ungetc ( c, stdin );
	while ( (c= getc (stdin ) )!= EOF)
	putchar ( c);
}
