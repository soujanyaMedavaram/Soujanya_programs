#include<stdio.h>

main()
{
	int *nums;
	int n, i;
	n = 0;
	nums = (int *)malloc(sizeof(int));
	for ( i = 0; i < 10000; i++)
	{
		*(nums + n) = i;
		n++;
		nums = (int *)realloc(nums, (n + 1) * sizeof(int));
	}
/*	for ( i = 0; i < 10000; i++ )
		printf( "%5d", *( nums + i ) );*/
}
