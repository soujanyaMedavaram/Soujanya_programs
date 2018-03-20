# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

main  ( ) {
	FILE *fp;
	char line[100];
	char *word, word2[50];
	int fd;

	word = ttyname ( 1 );
	printf ( "<%s>->ttyname\n", word );
	fp = fopen ( "config.sb", "r" );
	while ( 1 ) {
		if ( !fgets ( line, 100, fp ))
			break;
		word = strtok ( line, " " );
		printf ( "%s\n", word );
		word = strtok ( NULL, " " );
		printf ( "%s\n", word );
	}
}


