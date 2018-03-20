# include <stdio.h>
# include <stdlib.h>

# define LEN	2

char * get_line ( FILE *fp );
main ( ) {
	char *line, *word ;
	printf ( "\n enter a string \n" );
	while ((line = get_line ( stdin )) != NULL )
	printf ( "\n <%s - line >\n" , line );
	get_line(NULL);
}
/*char * get_word ( char *line ) {
	char word[20];
	static int i = 0;
	int j =0;

	while ( line[i] != '\0' && line[i] != ' ' && line[i] != '\n')
			word[j++] = line[i++];
	if ( line[i] == ' ' || line[i] == '\n')	i++;
	word[j] = '\0';
	if ( line[i] != '\0' )
		return word;
	else return NULL;
}*/

char * get_line ( FILE *fp ) {
	static char *line = NULL;
	static int len = 0;
	int offset;

	if ( fp == NULL ) {
		free ( line ); return NULL;
	}
	if ( !len ) line = malloc ( len = LEN );
	offset = 0;
	while ( 1 ) {
		if ( fgets ( line+offset, len - offset, fp ) == NULL ) {
			if ( offset ) return line;
			else return NULL;
		}
		if ( line [strlen ( line ) - 1 ] != '\n'  )
			line = realloc ( line, len += LEN );
		else {
			line[strlen ( line) - 1  ] = '\0';
			if ( line [strlen(line) - 1 ] != '\\' ) {
				line[strlen(line)] = '\n';
				line[strlen(line)+1] = '\0';
				return line;
			}
			line [strlen(line) - 1 ] = ' ';
		}
		offset = strlen ( line );
	}
}

