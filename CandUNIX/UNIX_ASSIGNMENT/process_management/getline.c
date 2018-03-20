# include <stdio.h>
# include <stdlib.h>

# define LEN	2

char * get_line ( FILE *fp );
char * get_word ( char *line );
main ( ) {
	char *line, *word ;
	printf ( "\n enter a string \n" );
	line = get_line ( stdin );
	printf ( "\n <%s - line >\n" , line );
	while ( ( word = get_word ( line )) != NULL )
		printf ( " <%s - word\n>", word );
}
char * get_word ( char *line ) {
	char *word;
	static int i = 0;
	int j =0;
	printf ( "\n %d - i\n", i );

	word = malloc ( 20 );
	while ( line[i] != '\0' && line[i] != ' ' )
		if (line[i] != '\n' )
			word[j++] = line[i++];
	if ( line[i] == ' ' )	i++;
	word[j] = '\0';
	if ( line[i] != '\0' )
		return word;
	else return NULL;
}

char * get_line ( FILE *fp ) {
	char *line = NULL;
	int len, offset;

	len = offset = 0;
	if ( fp == NULL ) {
		free ( line ); return NULL;
	}
	if ( !len ) line = malloc ( len = LEN );
	while ( 1 ) {
		if ( fgets ( line+offset, len - offset, fp ) == NULL ) {
			if ( offset ) return line;
			else return NULL;
		}
		if ( line [strlen ( line ) - 1 ] != '\n' )
			line = realloc ( line, len += LEN );
		else {
			line[strlen ( line) - 1  ] = '\0';
			if ( line [strlen(line) - 1 ] != '\\' ) {
				line [strlen ( line )  ] = '\n';
				line [strlen ( line ) + 1 ] = '\0';
				return line;
			}
			line [strlen(line) - 1 ] = ' ';
		}
		offset = strlen ( line );
	}
}

