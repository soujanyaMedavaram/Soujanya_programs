# include <stdio.h>
# include <string.h>

# define MAXLINE	5000


char *lineptr[MAXLINE];

int readlines (char *lineptr[], int nlines);
void writelines (char *lineptr[], int nlines);

void qsort (char *lineptr[], int left, int right);

main()
{
	int nlines;
	
	if ((nlines = readlines(lineptr,MAXLINE)) >= 0) {
		qsort (lineptr, 0, nlines - 1);
		writelines (lineptr,nlines);
		return 0;
	} else {
		printf ("error: input too big to sort\n");
		return 1;
	}
}

# define MAXLEN 1000
int getline(char *, int);
char *malloc(int);

int readlines (char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLINE];

	nlines = 0;
	while ((len = getline (line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy (p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

int getline(char line[], int max)
{
	int c, i = 0;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n';++i)
		line[i] = c;
	if (c == '\n')
	{
		line[i] = c;
		++i;
	}
	line[i] = '\0';

	return i;
}
	

void writelines (char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf ("%s\n", *lineptr++);
}

void qsort (char *v[], int left, int right)
{
	int i, last;
	void swap (char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for ( i = left + 1; i <= right; i++)
		if (strcmp(v[i],v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap (char *v[], int i, int j)
{
	char *temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

