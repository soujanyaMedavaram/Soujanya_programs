#include<stdio.h>

main()
{
	int *nums, *old;
	int n, i;
	n = 0;
	nums = (int *)malloc(sizeof(int));
	while (1)
	{
		if ( scanf( "%d", nums + n) != 1)
			break;
		n++;
		old = nums;
		nums = (int *)malloc((n + 1)*sizeof(int));
		memcpy( (char *) nums, (char *) old, n * sizeof(int));
	}
	printf("\n The elements in the array are \n");
	for ( i = 0; i < n; i++)
		printf( "%d\t", *(nums + i));
}
