# include <stdio.h>
# include <string.h>

# define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

void ungets(char s[])
{
	int len = strlen(s);
	void ungetch(int);

	while (len > 0)
		ungetch(s[--len]);
}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf ("ungetch: too amny characters\n");
	else
		buf[bufp++] = c;
}

main ()
{
	char s[25];
	printf("\n enter the string \n");
	scanf("%s",s);
	ungets(s);
}
