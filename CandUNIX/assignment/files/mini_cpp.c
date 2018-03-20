# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//# define DETAILED_ERR

void in_to_out ( char *infile, FILE *out );

char **filename = NULL;
int file_ind = 0;

main ( int argc, char *argv[])
{
	FILE *out;
	if ( argc != 3 ) {
		fprintf ( stderr, "Usage:<infile> <outfile>\n" );
		exit ( 1 );
	}
	if ( (out = fopen ( argv[2], "w" )) == NULL ) {
		printf ( "%s -- can not be opened \n",*argv[2] );
		exit ( 2 );
	}
	in_to_out ( argv[1], out );
	fclose ( out );
	return 0;
}

void in_to_out (char *infile, FILE *out)
{
	FILE *in;
	int c, i, line_no;
	char str[500], *p, path_str[100];
	char word[40], temp;

	if ( (in = fopen ( infile, "r")) == NULL) 
		return;
	line_no = 0;
	while ( fgets(str, 500, in) ) {
		line_no++;
		for ( p = str; *p == ' ' || *p == '\t'; p++ ) ;
		if ( *p != '#' ) {
			fprintf ( out, "%s", str );
			continue;
		}
		for ( p++; *p == ' ' || *p == '\t'; p++ ) ;
		for ( i = 0; islower (*p); p++, i++ ) word[i] = *p;
		word[i] = '\0';
		if ( !strcmp ( word, "include" ) ) {
			while ( *p == ' ' || *p == '\t' ) p++;
			if ( *p == '<' ) temp = '>';
			else if ( *p == '"' ) temp = '"';
			else {
				fprintf ( stderr, "File %s  Line %d: include directive error\n",
							infile, line_no );
				continue;
			}
			for (p++, i = 0; *p && *p != temp; p++,i++) word[i] = *p;
			word[i] = '\0';
			if ( !*p ) {
				fprintf ( stderr, "File %s  Line %d: improper include\n",
							infile, line_no );
				continue;
			}
			for ( i = 0 ; i < file_ind; i++) 
				if ( !strcmp ( word, filename[i] ))
					break;
			if ( i == file_ind ) {
				filename = realloc ( filename, ++file_ind * sizeof (char *) );
				filename[file_ind - 1] = strdup(word);
				if ( temp == '"')
					in_to_out ( word, out );
				else {
					strcpy (path_str, "/usr/include/");
					strcat (path_str, word);
					in_to_out ( path_str,out );
				}
			}
			continue;
		}
		fprintf ( out, "%s", str );
#		ifdef DETAILED_ERR
			if ( !strcmp ( word, "define" ) ) {
					fprintf ( stderr,
						"File %s  Line %d:# define not yet implemented\n",
						infile, line_no );
			} else if ( !strcmp ( word, "ifdef" ) ) {
				fprintf ( stderr, "# ifdef not yet implemented\n" );
			} else if ( !strcmp ( word, "else" ) ) {
				fprintf ( stderr, "# else not yet implemented\n" );
			} else if ( !strcmp ( word, "ifndef" ) ) {
				fprintf ( stderr, "# ifndef not yet implemented\n" );
			} else if ( !strcmp ( word, "endif" ) ) {
				fprintf ( stderr, "# endif not yet implemented\n" );
			} else if ( !strcmp ( word, "if" ) ) {
				fprintf ( stderr, "# if not yet implemented\n" );
			} else {
				fprintf ( stderr, "File %s Line %d: illegal directive %s\n",
							infile, line_no, word );
			}
#		endif
	}
	fclose (in);
}
