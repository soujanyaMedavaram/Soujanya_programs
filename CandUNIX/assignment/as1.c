#include<stdio.h>
main()
{
	char a[10];
	int n,i;
	printf("\n enter the string\n");
	scanf("%x",a);
	for(i=0;i!='\0';i++)
		if(a[i]>40)
		printf("%c",a[i]);		
}
