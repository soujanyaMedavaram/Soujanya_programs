# include <stdio.h>

void func ( int i, int &j, int *k ); 
main ( ) {
	int i = 1, j = 4, k = 16, m;
	func ( i, j, &k );
	m = i+j+k;
	printf ( "%d", m );
}
void func ( int i, int &j, int *k ) {
	i = 2;
	j = 16;
	*k = 32;
}
