# include <stdio.h>
# include <stdlib.h>

char * get_line ( FILE * );
char * get_word ( char * line );

main ( int argc, char *argv[] ) {
	FILE *fp;
	char *line, *word;
	while ( *++argv ) {
		fp = fopen ( *argv, "r" );
		while ( (line = get_line ( fp ) ) != NULL ) {
			printf ( "<%s>\n" , line );
			while ( word = get_word ( line ) ){
				line = NULL;
				printf ( "<%s>->word\n  ", word );
			}
		}
	}
}

char * get_line ( FILE *fp ) {
	static int len =0;
	static char *line;
	char *p;
	int offset;
# define LEN 20

	if ( fp == NULL ) {
		free ( line );
		return NULL;
	}
	if ( !len ) line = malloc ( len = LEN );
	offset = 0;
	while ( 1 ) {
		if ( fgets ( line + offset, len - offset, fp ) == NULL ) {
			if ( offset ) return line;
			else return NULL;
		}
		if ( line[strlen(line) - 1] != '\n' )
			line = realloc ( line, len += LEN );
		else {
			line[strlen(line) - 1] = '\0' ;
			if ( line[strlen(line) - 1] != '\\' ) {
				if ( line[0] != '\t' || line[0] == '\t') {
				p = line;
					while (isblank( *p ) ) p++;
					if ( *p == '#' || *p == '\n' || *p == '\0')
						get_line ( fp );
				}
				return line;
			}
			line[strlen(line) - 1 ] = ' ' ;
		}
		offset = strlen(line);
	}
}

char * get_word ( char * curr_line ) {
	static char * line;
	static char * word = NULL;
	static int len = 0;
	int k = 0;

	if ( curr_line != NULL )
		line = curr_line;
	if ( len <= strlen (line) )
		word = realloc ( word, strlen(line) + 1 );
	if ( *line == '\0' ) return NULL;
	while ( isblank ( *line ) ) line++;
	if ( *line == '#' || *line == '\n' ) return NULL;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}
