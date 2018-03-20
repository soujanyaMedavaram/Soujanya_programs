#include<stdio.h>
#define SIZE 100
main()
{
	int j,c,i,occ[SIZE],k=65;
	printf("enter the string");
	while((c=getchar())!=EOF)
	{
		if(c>='A'&&c<='Z')
			++occ['c'-'65'];
	}
	for(i=0;i<26;i++)
	{
		printf("%c:",k);
		k++;
		for(j=0;j<occ[i];j++)
	 		printf(".");
		printf("\n");
	}
}

