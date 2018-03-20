# include <stdio.h>

struct x { int i; int j; int k; };
struct x *p, *p1, arr[3], arr1[3] ;

main ( ) {
	int i;

	p = &arr[0];
	p1 = &arr1[0];
	//i = p + p1;
	//printf ( "p +p1 -> %d\n", i );
	i = p - p1;
	printf ( "p - p1 -> %d\n", i );
}
