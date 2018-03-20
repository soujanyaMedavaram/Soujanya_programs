# include <stdio.h>

void mycpy(char *s, char *t);
main()
{
	char c = 'a';
	char *s,*t;
	s = (char *)malloc(20);
	t = (char *)malloc(20);
	printf("\n enter a string\n");
	scanf("%s",t);
	mycpy(s,t);
	printf("\n s = %s\n", s);
}
void mycpy(char *s, char *t)
{
	int c;
	while((c = (*s++ = *t++)) )
	{
	if(c == '\0')
		printf("null");
	printf("\n %c\n",c);;
	}

}
