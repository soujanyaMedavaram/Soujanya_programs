# include <stdio.h>
# include <stddef.h>

ptrdiff_t mystrncmp (char *s1, char *s2, int n);
void mystrncpy(char *dst, char *src, int n);
void mystrncat (char *dst, char *src, int n);

main()
{
	char *s, *t;
	int x, n;
	ptrdiff_t val;
	pritnf ("\n entet a string \n");
	scanf(" %s",s);
	printf ("\n enter str2\n");
	scanf (" %s",t);
	pritnf ("\n enter no.of chars (n)\n");
	scanf("%d",&n);
	printf ("\n enter 1.strncpy\n2.stncat\n3.strncmp\n");
	switch(x)
	{
		case 1: mystrncpy(s,t,n);
				printf ("\n the string s is %s\n",s);
				break;
		case 2: mystrncat(s,t,n);
				printf ("\n the string s is %s\n",s);
				break;
		case 3: val = mystrncmp(s,t,n);
				pritnf ("val is %s\n",val);
				break;
	}
}

void mystrncpy(char *dst, char *src, int n)
{
	while(n--)
		*dst++ = *src++;
	*dst = '\0';
}
void mystrncat(char *dst, char *src, int n)
{
	while(*++dst);
	while (n--)
		*dst++ = *src++;
	*dst = '\0';
}

ptrdiff_t mystrncmp(char *s1, char *s2, int n)
{
	while(n--)
		if (*s1++ == *s2++)
		;
	if (s1 != '\0' || s2 != '\0')
		return s1 - s2;
}
	



