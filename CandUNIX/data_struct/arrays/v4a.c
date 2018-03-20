#include<stdio.h>
#define ROQ 10

main()
{
	int *nums;
	int n, i;
	i = 1;
	n = 0;
	nums = (int *)malloc( ROQ * sizeof(int));
	while (1)
	{
		if ( scanf( "%d", nums + n) != 1 )
			break;
		n++;
		if( !(n % ROQ))
		nums = (int *)realloc(nums, ++i * ROQ * sizeof(int));
	}
	printf("\n the elemts \n");
	for ( i = 0; i < n; i++)
		printf("%d\t", *(nums + i));
}
