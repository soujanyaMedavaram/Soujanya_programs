# include <stdio.h>
# include <string.h>
# include <stdlib.h>

char * get_word ( FILE *fp );
main ( int argc, char ** argv ) {
	FILE *fp;
	char *word;
	while ( *++argv ) {
		fp = fopen ( *argv, "r" );
		while ( (word = get_word ( fp )) ) {
			printf ( "<%s>\n", word );
			if ((strcmp ( word, "\t" ) == 0 )) {
				while ( word = get_word ( fp ))
					if ( strcmp (word, "\n") == 0)
						break;
			}
		}
	}
	return 0;
}

char * get_word ( FILE *fp ) {
	int c, j;
	static int prev_c;
	static char word[100];
	j = 0;
//	printf ( "prev_c-><%c>\n", prev_c );
		
	while ( ( c= getc ( fp ) ) != EOF )   {
		if ( prev_c == '\t' && j == 0 ) {
			word[j++] = '\t';
			word[j] = '\0';
			fseek ( fp, -1, SEEK_CUR );
			prev_c = c;
			return word;
		}
		if ( ( prev_c == '\n' )) {
			word[j++] = prev_c;
			word[j] = '\0';
			prev_c = c;
			if ( c != '\t' && c != '\n' )
				fseek ( fp, -1, SEEK_CUR );
			return word;
		}
		if ( c != ' ' && c != '\t' && c != ':' && c!= '\n') {
			word[j++] = c;
			prev_c = c;
			continue;
		}
		else if (  j != 0 && c == ' ' || c == '\t' || c == ':' || c == '\n' ) {
			word[j] = '\0';
			prev_c = c;
			if ( word[0] != '\0' )
				return word;
		}
		if ( (c == ':' && prev_c != ':' )|| ( prev_c == ':' && c != ':' ) ) {
			word[j++] = ':';
			word[j] = '\0';
			if ( c != ':' )
				prev_c = c;
			return word;
		}
		if ( c == '\t' && prev_c == '\n' && j == 0 ) {
			word[j++] = '\t';
			word[j] = '\0';
			c = prev_c;
			return word;
		}
		if ( c == '\n' || prev_c == '\n' ) {
			word[j++] = c;
			word[j] = '\0';
			prev_c = c;
			return word;
		}
	}
	if ( prev_c == '\n' ) {
		word[j++] = '\n';
		word[j] = '\0';
		prev_c = '\0';
		return word;
	}
	return NULL;
}
