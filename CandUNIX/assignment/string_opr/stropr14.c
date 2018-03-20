#include<stdio.h>
#define SIZE 100

void insert_string(char *dst,char *src, int pos);

main ()
{
	char src[SIZE],dst[SIZE];
	int pos = 0, c;
	printf( "\n enter the line\n" );
	while (( c=getchar() ) != EOF && c != '\n')
	dst[pos++]=c;
	dst[pos] = '\0';
	printf( "\n enter the string to be stuffed \n");
	scanf( "%s",src);
	printf("\n enter the position wher to insert the string \n");
	scanf("%d",&pos);
	insert_string(dst,src,pos);
}

void insert_string(char *dst, char *src, int pos)
{
	int j,i;
	for( i = strlen(dst) + strlen(src), j = strlen(dst); j >= pos; i--,j--)
		dst[i] = dst[j];
	for( i = 0, j = pos; i < strlen(src); j++,i++)
		dst[j] = src[i];
	printf("%s\n",dst);
}
