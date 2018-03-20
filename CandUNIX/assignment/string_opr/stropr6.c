#include<stdio.h>
#include<string.h>
#define MAX 100

int getline(char *line, int max);    /*reads input, converts vowels to capital*/

main()
{
	char line[MAX];
	printf("\n enter the input \n");
	while(getline(line,MAX ) > 0)
	{
		printf("\n The line with vowels capital letters is \n");
		printf("%s\n",line);
	}
}

int getline(char *line, int max)
{
	int c;
	int count = 0;

	while( --max > 0 && (c = getchar()) != EOF && c != '\n')
	{
		switch(c)
		{
			case 'a': 
			case 'e':
			case 'i': 
			case 'o': 
			case 'u': c = toupper(c);
					  break;
		}
		line[count++] = c;
	}
	if(c == '\n')
		line[count++] = '\n';
	line[count] = '\0';
	return count;
}

