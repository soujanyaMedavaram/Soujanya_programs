#include<stdio.h>
#define MAX 100

main(int argc, char *argv[])
{
	char word[MAX];
	int collect = 0, i, c;
	int count[argc];
	for(i = 1; i < argc; i++)
		count[i] = 0;
	if(argc < 2)
	{
		fprintf(stderr,"Usage a.out <word> <word>...");
		exit(1);
	}
	while(( c = getchar()) != EOF)
	{ 
 		if(c == '\n' || c == '\t' || c == ' ')
		{
			word[collect] = '\0';
			collect = 0;
			for(i = 1; i < argc; i++)
				if(strcmp(argv[i],word) == 0)
					count[i]++;
		}
	else
		word[collect++] = c;
	}
	printf("the no. of occurences of the words is \n");
	for(i = 1; i < argc ;i++)
		printf("%s  -  %d\n",argv[i],count[i]);
}
