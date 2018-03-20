#include<stdio.h>
#define SIZE 100
void mystrcpy(char *dst,char *src);
main()
{
	char *src, *dst;
	char* malloc(int);
	src = malloc(SIZE);
	dst  = malloc(SIZE);
	printf("\n enter a string\n");
	scanf("%s",src);
	mystrcpy(dst,src);
	printf("\n main: the string in destion is %s",dst);
}

void mystrcpy(char *dst,char *src)
{
	char *temp;
	temp=dst;
	while( *dst++ = *src++ );
	//*dst++ = *src++;
	//*dst = '\0';
	printf("the string in destination is %s",temp);
}
