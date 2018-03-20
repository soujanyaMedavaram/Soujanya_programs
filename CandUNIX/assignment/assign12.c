# include <stdio.h>

# define TRUE	1
# define FALSE	0

void print_last (char *file, int nlines);

main (int argc, char *argv[]) {
	int nlines = 5, c;
	int no_file = TRUE;
	FILE *fp;

	while (*++argv) {
		if (**argv == '-') {
			if ( isdigit (++*argv) )
				nlines = atoi(*argv);
			continue;
		}
		print_last(*argv,nlines);
		no_file = FALSE;
	}
	if (no_file == TRUE) {
		fp = fopen("data.dat", "w");
		while ((c = getchar()) != EOF)
			putc(c,fp);
		fclose(fp);
		print_last("data.dat",nlines);
	}
}

void print_last(char *file, int nlines) {
	int c, rest_lines, f_lines, line_count;
	FILE *fp;

	f_lines = line_count = 0;
	if ((fp = fopen(file, "r")) == NULL) {
		fprintf (stderr,"file %s can not be opened\n",file);
		return;
	}
	printf ("\n ========== %s ==========\n",file);
	while ((c = getc(fp)) != EOF)
		if (c == '\n')
			f_lines++;
	rewind(fp);
	rest_lines = f_lines - nlines;

	if ( rest_lines > 0 )
		while ( (c = getc(fp)) != EOF )
			if ( c == '\n' && ++line_count >= rest_lines )
				break;
	while ((c = getc(fp)) != EOF)
		putchar (c);
	fclose (fp);

/*	while ((c = getc(fp)) != EOF)
	{
		if (c == '\n')
			line_count++;
		if (line_count >= rest_lines)
			putchar(c);
	} */
}
