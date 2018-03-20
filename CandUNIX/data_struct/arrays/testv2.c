#include<stdio.h>

main()
{
	int *nums, nmax, i;
	printf("\n enter the no of ints \n");
	scanf("%d",&nmax);
	nums = (int *)malloc(nmax * sizeof(int));
	printf( "\n enter the elemets \n");
	for( i = 0; i < nmax; i++)
	scanf( "%d", &nums[i]);
	printf( " tthe elements in the array are \n");
	for( i = 0; i < nmax; i++)
	printf("%d",nums[i]);
}

