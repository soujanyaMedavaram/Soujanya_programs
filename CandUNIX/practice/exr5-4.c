# include <stdio.h>

main()
{
	char s[20], t[20];
	int x;
	printf ("\n entert he str1\n");
	scanf(" %s",s);
	printf ("\n entert the str2 \n");
	scanf(" %s",t);
	x = mystrend(s,t);
	printf ("\n x = %d\n",x);
}

int mystrend(char *s, char *t)
{
	char *bt;
	bt = t;
	while(*s++);
	while(*t++);
	while (*--s == *--t);
	*t++;
	if ( t == bt )
		return 1;
	else return 0;
}

