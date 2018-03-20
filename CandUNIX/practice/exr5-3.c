# include <stdio.h>

void mystrcat (char *s, char *t);

main()
{
	char s[20],t[20];
	printf ("\n enter strin1\n");
	scanf (" %s",s);
	printf ("\n enter string2\n");
	scanf (" %s",t);
	mystrcat(s,t);
	printf ("the string s is %s\n",s);
}

void mystrcat(char *s, char *t)
{
	while (*++s) 
	//while(*s++); in this case 1st incremented and then dereferenced
	;
	//*s--;
	while (*s++ = *t++)
	;
}

