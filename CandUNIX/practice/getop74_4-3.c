# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define NUMBER '0'
# define BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int c,i;

	while ((s[0] = c= getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if (!isdigit(c) &&c != '.' && c != '-')
		return c;
	if (c == '-')
		if (isdigit(c = getch()) || c == '.')
			s[++i] = c;
		else
		{
			if (c != EOF)
				ungetch(c);
			return '-';
		}
	if (isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
		s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch()
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf ("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
