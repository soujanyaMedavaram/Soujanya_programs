#include<stdio.h>

main()
{
	int *nums, *old;
	int n, i, j;
	n = 0;
	nums = (int *)malloc(sizeof(int));
	for ( j = 0; j < 10000; j++)
	{
		*(nums + n) = j;
		n++;
		old = nums;
		nums = (int *)malloc((n + 1) * sizeof(int));
		memcpy((char *) nums, (char *) old, n * sizeof(int));
	}
}
