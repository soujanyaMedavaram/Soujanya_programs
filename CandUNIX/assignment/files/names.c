#include<stdio.h>

main()
{
	char a[50][50],i;
	printf("\n enter names \n");
	for( i=0; i< 5; i++)
		scanf("%s",a[i]);
	for( i= 0; i< 5; i++)
		printf("%s\n",a[i]);
}
