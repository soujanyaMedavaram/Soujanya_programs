#include<stdio.h>
#include<ctype.h>

#define SIZE 1000

main()
{
	char c,str[SIZE],substr[SIZE];
	char u[] = "unix";
	int i, j=0, slen;
	printf("\n enter the string line \n");
	for(i=0;i<SIZE && (c=getchar())!=EOF && c!='\n';i++)
		str[i]=c;
	if(c=='\n')
		str[i]='\0';
	slen = strlen(str);
	for(i=0; i <= slen+1 ;i++)
	{
		if(str[i]!=' ' && str[i] != '\0')
		{
			substr[j]=str[i];
			j++;
		}
		else if(str[i]==' ' || str[i] == '\0')
		{
			substr[j]='\0';
			if(strcmp(substr,u)==0)
			{
				printf("\n%s",str);
				break;
			}
			j=0;
		}
	}
}
