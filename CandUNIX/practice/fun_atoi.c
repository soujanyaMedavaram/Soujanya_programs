#include<stdio.h>

int atoi(char *s);

main()
{
	char str[20];
	int integer;
	printf("\n enter a string\n");
	scanf("%s",str);
	integer=atoi(str);
	printf("the integer valive of string is %d",integer);
}
int atoi(char *s)
{
	int i=0;
	while(*s)
	{
		i=(i<<3)+(i<<1)+(*s-'0');
		s++;
	}
	return i;
}
