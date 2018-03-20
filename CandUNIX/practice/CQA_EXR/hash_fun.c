# include <stdio.h>
# include "hash.h"

int hash_fun ( char *s, int tot ) {
	int i, keyval, ind;

	i = 1, keyval = 0;
	while ( s[i] != '\0' )
	{
		keyval += s[i];
		i = i + 1;
	}
	ind = ( keyval % tot ) + 1;
	return ind;
}
