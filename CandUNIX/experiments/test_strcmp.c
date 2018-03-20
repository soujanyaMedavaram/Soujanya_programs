# include <stdio.h>
# include <string.h>

main ( ) {
	char str1[] = "a", str2[] = "d";
	int n;
	n = strcmp ( str1, str2 );
	printf ( "%d\n", str1[0] - str2[0] );
	printf ( "%d\n", strcmp ( str1, str2 ) );
	printf ( "n = %d\n", n );
}
