# include <stdio.h>
# include "utils.h"

main ( ) {
	char *line, *word ;
	printf ( "\n enter a line\n" );
	line = get_line ( stdin );
	printf ( "<%s>\n", line );
	while (	word = get_word ( line ) ) {
		line = NULL;
		printf ( "<%s>\n", word );
	}
}

