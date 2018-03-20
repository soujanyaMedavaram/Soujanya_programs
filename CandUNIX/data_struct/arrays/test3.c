#include<stdio.h>
main()
{
	int a[10000],i;
	for ( i = 0; i < 10000; i++)
		a[i] = i;
	for ( i = 0; i < 1000; i++)
		printf("%d",a[i]);
}
