/* when unsigned int is complared with signed int, then signed int is looked
	as an unsigned int. Here, 2^32 = 4GB = 4294967296. So, -1 means 
	4294967296 - 1 = 4294967295. 4 * 1024(1k) * 1024(1M) * 1024(1G).
*/
# include <stdio.h>

int main ( void ) {

	unsigned int i = -2;
	if ( sizeof (int) > i )
		printf ( "greater\n" );
	else printf ( "smaller\n" );
	printf ( "i: %u\n", -2 );
	return 0;
}
