#include<stdio.h>
#define ROQ 10

main()
{
	int *nums;
	int n, i, m, j;

	n = 0;
	m = 1;
	nums = (int *)malloc(ROQ * sizeof(int));
	for ( i = 0; i < 1000; i++)
	{
		*(nums + n) = i;
		n++;
		if ( !(n % ROQ) ) 
			nums = (int *)realloc(nums, ++m * ROQ * sizeof(int));
	}
	/*printf("\n the elemts \n");
	for ( j = 0; j < i; j++)
		printf("%d\n", *(nums + j));*/
}
