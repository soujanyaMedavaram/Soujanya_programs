
# include <stdio.h>
# include <stdlib.h>

char * get_word ( FILE * fp ) ;
main ( int argc, char ** argv ) {
	FILE *fp;
	char*word;
	*++argv;
	fp = fopen ( *argv, "r" );
	while ( (word = get_word ( fp )) != NULL )
		printf ( "<%s>\n", word);
	
}

# define ROQ	50

char * get_word ( FILE * fp ) {
	int c, j;
	static char * word = NULL;
	static int len = 0;
	static int line_begins;
	static long save_pos;
	static FILE * sfp = NULL;
	int escape;

	if ( fp == NULL ) {
		while ( ( c = getc (sfp) ) != '\n' && c != EOF ) ;
		return;
	}
	if ( fp != sfp || ftell (fp) != save_pos )
		line_begins = 1;
	sfp = fp;
	escape = 0;
	while ( ( c = getc ( fp ) ) != EOF ) {
		save_pos = ftell (fp);
		if ( escape ) {
			if ( c != '\n' ) break;
			escape = 0;
			continue;
		}
		if ( c == '\\' ) {
			escape = 1; continue;
		}
		if ( c == '\t' && line_begins ) {
			line_begins = 0;
			return "\t";
		}
		line_begins = 0;
		if ( c == ' ' || c == '\t' ) continue;
		if ( c == '#' ) {
			get_word (NULL);
			line_begins = 1;
			continue;
		}
		if ( c == '\n' ) {
			line_begins = 1;
			return "\n";
		}
		if ( c == ':' ) return ":";
		break;
	}
	if ( c == EOF ) return NULL;
	j = 0;
	goto process_character;
	while ( 1 ) {
		c = getc (fp);
		process_character:
			if ( escape ) escape = 0;
			else {
				if ( c == '\\' ) escape = 1;
				else if ( c == ' ' || c == '\t' || c == '\n' ||
						c == ':' || c == EOF ) {
					if ( c == ':' || c == '\n')
						ungetc (c, fp);
					word[j] = '\0';
					return word;
				}
			}
			if ( j >= len )
				word = realloc ( word, (len += ROQ) + 1 );
			word[j++] = c;
	}
}
