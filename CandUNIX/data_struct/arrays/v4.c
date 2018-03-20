#include<stdio.h>

main()
{
	int *nums;
	int n, i;

	n = 0;
	nums = (int *)malloc(sizeof(int));
	while (1)
	{
		if ( scanf( "%d", nums + n) != 1 )
			break;
		n++;
		nums = (int *)realloc(nums, (n + 1) * sizeof(int));
	}
	printf("\n the elemts \n");
	for ( i = 0; i < n; i++)
		printf("%d\t", *(nums + i));
}
