#include<stdio.h>

main()
{
	int *nums, *old;
	int *src, *dst;
	int n, i, j;
	n = 0;
	nums = (int *)malloc(sizeof(int));
	for ( j = 0; j < 10000; j++)
	{
		*(nums + n) = j;
		n++;
		old = nums;
		nums = (int *)malloc((n + 1) * sizeof(int));
		src = old;
		dst = nums;
		for ( i = 0; i < n ; i++)
			*dst++ = *src++;
	}
	
}
