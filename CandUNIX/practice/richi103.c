# include <stdio.h>
# include <stddef.h>

size_t mystrlen(char *s);
/* we can replace size_t with prtdiff_t also
refer ritchi 103*/

main()
{
	char s[20];
	size_t len;
	printf ("\n enter the string\n");
	scanf("%s",s);
	len = mystrlen(s);
	printf ("\n the strlength is %d\n",len);
}

size_t mystrlen(char *s)
{
	char *p = s;
	while (*p != '\0')
		p++;
	return p - s;
}

