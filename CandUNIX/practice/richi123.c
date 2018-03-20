# include <stdio.h>
# include <ctype.h>
# include <string.h>
# define MAXTOKEN	100
# define BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl(void) {
	int ns;
	for ( ns = 0; gettoken () == '*'; )
		ns++;
	dirdcl ( );
	while ( ns-- > 0 )
		strcat ( out, "pointer to ");
}

void dirdcl(void) {
	int type;

	if ( tokentype == '(' ) {
		dcl();
		if (tokentype != ')' )
			printf ( "Error:Missing )\n" );
	} else if ( tokentype == NAME )
		strcpy ( name, token );
	else
		printf ( "Error:Expected name or (dcl)\n" );
	while ( ( type = gettoken() ) == PARENS || type == BRACKETS )
		if ( type == PARENS )
			strcat ( out, "function returning" );
		else {
			strcat ( out, "array" );
			strcat ( out, token );
			strcat ( out, "of");
		}
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch ( int c ) {
	if ( bufp >= BUFSIZE )
		printf ( "ungetch: too amny characters \n");
	else
		buf[bufp++] = c;
}

main ( ) {
	while ( gettoken() != EOF ) {
		strcpy (datatype, token );
		out[0] = '\0';
		dcl();
		if ( tokentype != '\n' )
			printf ( "\nSyntax Error\n");
		printf ( "%s: %s %s\n", name, out, datatype );
	}
	return 0;
}

int gettoken(void) {
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ( (c= getch()) == ' ' || c == '\t' );
	if ( c == '(' ) {
		if ( (c =getch() ) == ' ' ) {
			strcpy ( token, "()" );
			return tokentype = PARENS;
		} else {
			ungetch ( c );
			return tokentype = '(' ;
		}
	} else if ( c == '[' ) {
		for (*p++ = c; (*p++ = getch()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c= getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}
