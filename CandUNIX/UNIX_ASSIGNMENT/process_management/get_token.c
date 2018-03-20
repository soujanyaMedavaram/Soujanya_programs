# include <stdio.h>
# include <stdlib.h>

	char word[20] ;
char * get_word ( char * line ) {
	static char *p;		
	int j;
//	word = malloc ( 20 );

	if ( line != NULL )
		p = line;
	for ( ; isblank ( *p ); p++ );
	for ( j = 0; *p != '\0';  p++ ) {
		if ( *p == ';' || *p == '|' || *p == '&' || 
			 isblank (*p) || *p == '\n' || *p == '>' || *p == '<' ) {
			word[j] = '\0';
			if ( word[0] != '\0' ) return word;
		}
		if ( *p == '\n' ) { p++; return "\n" ; }
		if ( *p == '<' ) { p++; return "<" ;}
		if ( *p == ';' ) { p++; return ";" ; }
		if ( *p == '|' && *(p + 1) == '|' ) { p += 2 ; return "||"; }
		else if ( *p == '|' ) { p++; return "|" ; }
		if ( *p == '&' && *(p + 1) == '&' ) { p += 2 ; return "&&"; }
		else if ( *p == '&' ) {p++; return "&" ; }
		if ( *p == '>' && *(p + 1) == '>' ) { p += 2 ; return ">>"; }
		else if ( *p == '>' ) {p++; return ">" ; }
		word[j++] = *p;
	}
	if ( *p == '\0' ) return NULL;
}
