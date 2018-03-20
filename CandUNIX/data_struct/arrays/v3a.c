#include<stdio.h>

main()
{
	int *nums, *old;
	int *src, *dst;
	int n, i;
	n = 0;
	nums = (int *)malloc(sizeof(int));
	while (1)
	{
		if ( scanf( "%d", nums+n) != 1 )
	 		break;
		n++;
		old = nums;
		nums = (int *)malloc((n + 1) * sizeof(int));
		src = old;
		dst = nums;
		for ( i = 0; i < n; i++)
			*dst++ = *src++;
	}
	printf(" \n the elements in the array are \n");
	for ( i = 0; i < n; i++)
		printf ( "%d", nums[i]);
}
	
		
