#include<stdio.h>
#define SIZE 100

main( int argc, char *argv[])
{
	char word[SIZE], str[SIZE];
	int c;
	int collect = 0;
	if(argc != 2)
	{
		fprintf(stderr, "usage: a.out <word>\n");
		exit(1);
	}
	sscanf(argv[1],"%s",str);
	printf("\n enter the input \n");
	while((c = getchar()) != EOF)
	{
		if(c == '\n' || c == '\t' || c== ' ')
		{
		word[collect] = '\0';
		collect = 0;
		if(strcmp(str,word) != 0)
			printf("%s%c",word,c);
		else 
			putchar(c);
		}
		else
			word[collect++] = c;
	}
}
