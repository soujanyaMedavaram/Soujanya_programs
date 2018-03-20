# include <stdio.h>

char *malloc (int);
char * realloc (char *, int);
void free (char *);

struct detail {
	char *word;
	int count;
	int *line_nos;
};

struct detail *details;
int nwords;

