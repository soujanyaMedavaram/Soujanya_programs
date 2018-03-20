# include <stdio.h>
int d;
main ( ) {
	int a;
	register int b;
	static int c;
	printf ( "%d->auto\n %d->reg\n %d->sta\n%d->global\n", a,b,c,d );
}
