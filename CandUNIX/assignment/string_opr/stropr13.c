#include<stdio.h>
#define MAX 100

main(int argc, char *argv[])
{
	char word[MAX];
	int collect = 0, i, c;
	if(argc < 2)
	{
		fprintf(stderr,"Usage a.out <word> <word>...");
		exit(1);
	}
	printf("\n enter the input \n");
	while(( c = getchar()) != EOF)
	{ 
 		if(c == '\n' || c == '\t' || c == ' ')
		{
			word[collect] = '\0';
			collect = 0;
			for(i = 1; i < argc; i++)
			{
				if(strcmp(argv[i],word) != 0)
					printf("%s",word);	
			}
			putchar(c);
		}
	else
		word[collect++] = c;
	}
}
