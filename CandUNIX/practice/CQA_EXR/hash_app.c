# include <stdio.h>
# include "hash.h"

# define TOTAL	100

main ( ) {
	char s[25], str[TOTAL][25];
	int ind[100], key, i;
	static int j = 0;

	while ( scanf ( " %s", s) != EOF) {
		key = hash_fun ( s, TOTAL );
		for ( i = 0; i < j; i++ ) {
			if (key == ind[i] ) {
				key++;
				i = 0;
				continue;
			}
			ind[j] = key;
		}
		ind[j] = key;
		strcpy ( str[ind[j]], s );
		j++;
	}
	for ( i = 0; i < j; i++ ) 
		printf ( "%s- %d\n", str[ind[i]], ind[i] );
}


