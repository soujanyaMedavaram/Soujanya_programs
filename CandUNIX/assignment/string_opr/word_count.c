#include<stdio.h>
#include<string.h>
#define SIZE 100

main(int argc, char *argv[])
{
    char word[SIZE],str[SIZE];
	int collect = 0, c, word_count = 0;
	sscanf(argv[1],"%s",str);
	printf("\n enter the string line \n");
	while((c=getchar())!=EOF)
	{
		if( c == '\n' || c == '\t' || c == ' ' )
		{
			word[collect] = '\0';
			collect=0;
			if(strcmp(str,word) == 0)
			 word_count++;
		}
		else
		word[collect++] = c;
	}
	printf("\n the num of occurences of the word %s id %d",str,word_count);
}
