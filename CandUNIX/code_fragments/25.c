# include <stdio.h>

void func ( int x ) {
	int count = 0;

	for ( ; x; x-- )
		if (!(x%10))
			count++;
	printf ( "%d - count \n" , count );

}
main ( ) {
	func ( 256 );
}
