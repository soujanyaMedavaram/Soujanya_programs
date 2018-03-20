#include<stdio.h>
#define MAX 1000
#define TRUE 1
#define FALSE 0

void getline(char *line, int max);
int find_string(char *line,char *substr);

main()
{
	char line[MAX],substr[100];
	int found;
	printf("\n enter a string line \n");
	getline(line,MAX);
	printf("\n enter the string to be searched\n");
	scanf("%s",substr);
	found=find_string(line,substr);
	if(found==TRUE)
		printf("\n String found \n");
	else
		printf("\n string not found\n");
}

void getline(char *line, int max)
{
	int c,i;
	for(i=0;--max>0&&(c = getchar()) != EOF && c != '\n'; i++)
		line[i]=c;
	if(c=='\n')
		line[i++]=c;
	line[i]='\0';
}

int find_string(char *line,char *substr)
{
	int i,j,k;
	for(i=0;line[i]!='\0';i++)
	{
		for(j=i,k=0;substr[k]!='\0' && line[j] == substr[k];k++,j++);
		if( k > 0 && substr[k] == '\0' )
		 return TRUE;
	}
	return FALSE;
}

