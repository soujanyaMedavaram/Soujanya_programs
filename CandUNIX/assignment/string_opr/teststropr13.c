#include<stdio.h>
#define MAX 1000

main(int argc, char *argv[])
{
	char word[MAX], line[MAX];
	int collect, i, c, j, flag;

	if(argc < 2)
	{
		fprintf(stderr,"Usage a.out <word> <word>...");
		exit(1);
	}

	printf("\n enter the input \n");
	for(collect = 0; (c = getchar()) != EOF; collect++)
		line[collect] = c;

	collect = flag = 0;	
	for(i = 0; i < strlen(line); i++)
	{ 
		c = line[i];		
 		if (c == '\n' || c == '\t' || c == ' ')
		{
			word[collect] = '\0';
			collect = flag = 0;
			for(j = 1; j < argc; j++) 
				if(strcmp(argv[j],word) == 0) {
					flag = 1;
					break;
				}
			if ( !flag ) printf ( "%s", word );
			putchar(c);
		}
		else
			word[collect++] = c;
	}
}
