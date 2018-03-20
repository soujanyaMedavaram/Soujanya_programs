# include <stdio.h>

# define TRUE	1
# define FALSE	0

void print_last (FILE *fp, int nlines);
void stdin_read ( FILE *fp , int nlines) {
	int c;
	fp = tmpfile ( );
	while ((c = getchar()) != EOF)
		putc(c,fp);
	print_last(fp,nlines);
	fclose(fp);
}

main (int argc, char *argv[]) {
	int nlines = 5, c;
	int no_file = TRUE;
	FILE *fp;
	while (*++argv) {
		if (**argv == '-') {
			if ( isdigit (*++*argv) )
				nlines = atoi(*argv);
			else 
			no_file = TRUE;
		}	else {
			no_file = FALSE;
			if ( (fp = fopen ( *argv, "r" ) ) == NULL ) {
				fprintf ( stderr, "file not opened \n" );
				continue;
			}
			print_last(fp,nlines);
			fclose ( fp );
		}
		if ( no_file == TRUE )
			stdin_read ( stdin , nlines);	
	}
	if (no_file == TRUE) 
		stdin_read ( stdin , nlines);
}

void print_last(FILE *fp, int nlines) {
	int c, rest_lines, f_lines, line_count;

	f_lines = line_count = 0;
	printf ("\n ==========file contents==========\n");
	rewind(fp);
	while ((c = getc(fp)) != EOF)
		if (c == '\n')
			f_lines++;
	rest_lines = f_lines - nlines;
	rewind(fp);
	if ( rest_lines > 0 )
		while ( (c = getc(fp)) != EOF )
			if ( c == '\n' && ++line_count >= rest_lines )
				break;
	while ((c = getc(fp)) != EOF)
		putchar (c);
	//fclose (fp);

/*	while ((c = getc(fp)) != EOF)
	{
		if (c == '\n')
			line_count++;
		if (line_count >= rest_lines)
			putchar(c);
	} */
}
