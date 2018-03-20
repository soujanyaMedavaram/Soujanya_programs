# include <stdio.h>
# include <string.h>

# define MAXLINES	5000
# define MAXLEN		1000

char *lineptr[MAXLINES];
char *malloc(int);

int readlines ( char *lineptr[], int nlines );
void writelines ( char *lineptr[], int nlines );
int numcmp (char *s1, char *s2);
int reverse = 0;
int getline ( char s[], int lim ) {
	int c, i;

	i = 0;
	while ( --lim > 0 && (c=getchar()) != EOF && c != '\n' )
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void qsort( void *lineptr[], int left, int right,int (*comp)(void *, void *));

main ( int argc, char *argv[] ) {
	int nlines;
	int numeric = 0;
	
	while (*++argv)
		if (**argv == '-') 
			while (*++*argv)
				if (**argv == 'n')
					numeric = 1;
				else if (**argv == 'r')
					reverse = 1;
				else {
					printf ("\n invalid argument\n");
					exit ( 1 );
				}
					
	
	if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
		qsort ( (void **) lineptr, 0, nlines-1,(int (*)(void *, void *))(numeric ? numcmp : strcmp) );
		writelines ( lineptr, nlines );
		return 0;
	} else {
		printf ( "\n input too big to sort\n" );
		return 1;
	}
}
void qsort ( void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap ( void *v[], int i, int j );

	if ( left >= right ) return;
	swap ( v, left, (left + right) / 2);
	last = left;
	for ( i = left + 1; i <= right; i++ ) {
		if (reverse == 1)
			if ( (*comp)(v[i], v[left]) > 0)
				swap ( v , ++last, i);
		else if ( (*comp)(v[i], v[left]) < 0 )
				swap (v, ++last, i);
	}
	swap (v, left, last);
	qsort (v, left, last-1, comp);
	qsort (v, last+1, right, comp);
}

int numcmp ( char *s1, char *s2 ) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap ( void *v[], int i, int j  ) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
void writelines (char *lineptr[], int nlines ){
	printf ( "\n sorted order is \n");
	while (nlines--  > 0)
		printf ("%s\n", *lineptr++);
}
int readlines ( char *lineptr[], int maxlines ) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline ( line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}



	
