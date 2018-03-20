# include <stdio.h>
# include <string.h>

void in_to_out ( char *infile, FILE *out );

char **filename;
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
	filename = (char **)malloc ( sizeof ( char * ) * 100 );
	in_to_out ( argv[1], out );
	fclose ( out );
	return 0;
}

void in_to_out (char *infile, FILE *out)
{
	FILE *in;
	int c, dup_file, i, line_no;
	char str[100], *p, path_str[100];
	char word[40], temp;

	dup_file = 0;
	if ( (in = fopen ( infile, "r")) == NULL) 
		return;
	line_no = 0;
	while ( fgets(str, 100, in) ) {
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
			if ( *p != '<' && *p != '"' ) {
				fprintf ( stderr, "File %s  Line %d: include directive error\n",
							infile, line_no );
				continue;
			}
			else temp = (( *p == '<' ) ? '>' : '"' );
			for (p++, i = 0; *p != temp; p++,i++) word[i] = *p;
			word[i] = '\0';
			for ( i = 0 ; i < file_ind; i++) 
				if ( !strcmp ( word, filename[i] )) {
					dup_file = 1;
					break;
			}
			if (dup_file != 1) {
				filename[file_ind++] = strdup(word);
				strcpy(path_str,"/usr/include/");
				strcat(path_str,word);
				dup_file = 0;
				in_to_out(path_str,out);
			}
		} else if ( !strcmp ( word, "define" ) ) {
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
		} 
		 else {
			fprintf ( stderr, "File %s Line %d: illegal directive %s\n",
						infile, line_no, word );
			continue;
		}
	}
}
