# include <stdio.h>
# include <string.h>

void in_to_out ( char *infile, FILE *out );

char *filename[100];
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
	return 0;
}
void in_to_out (char *infile, FILE *out)
{
	FILE *in;
	int c, count, inc_flag, indx, collect, i, file_dup;
	char str[100], path_str[100];

	indx = count = inc_flag = collect = file_dup = 0;
	if ( (in = fopen ( infile, "r")) == NULL) 
		return;
	while ( (c = getc(in)) != EOF ) {
		if ( c == '#' ) count = 1;
		if ( count == 1 && c != '#' && c != ' ' && collect != 1) {
			str[indx++] = c;
			str[indx] = '\0';
		}
		if ( (strcmp (str, "include") == 0) && inc_flag == 0) {
			inc_flag = 1;
			indx = 0;
			count = 0;
		}
		if ( inc_flag == 1 && c == '<' ) {
			collect = 1; 
			indx = 0;
		}
		if ( c == '>' && collect == 1) {
			for ( i = 0; i < file_ind; i++)
				if ( strcmp(filename[i],str) == 0 ) {
					file_dup = 1;
					break;
				}
			if ( file_dup != 1)
			{
				filename[file_ind++] = strdup(str);
				strcpy(path_str, "/usr/include/");
				strcat (path_str, str);
				putc ( c, out );
				file_dup = 0;
				in_to_out ( path_str, out);
			}
		}
		if ( collect == 1 && c != '<' && c != '>') {
			str[indx++] = c;
			str[indx] = '\0';
		}
		if ( c == '\n' ) {
			count = 0;
			indx = 0;
			collect = 0;
		}
		putc (c , out);
	}
}
