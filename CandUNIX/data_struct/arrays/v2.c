#include<stdio.h>
#define HUGE 20

int nmax,  n, i;
int *nums;
main()
{
	printf( "no. of ints = ");
	if (scanf("%d", &nmax) != 1)
	{
		fprintf(stderr, "don't play here \n");
		exit(1);
	}
	if (nmax < 1 || nmax > HUGE)
	{
		fprintf(stderr, "why don't you be serious\n");
		exit(2);
	}
	nums = (int *) malloc (nmax * sizeof(int));
	printf("\n enter elements\n");
	for( i = 0; i < nmax; i++)
		scanf("%d",&nums[i]);

	printf("\n the array elements are \n");
	for( i = 0; i < nmax; i++)
		printf("%d",nums[i]);
}
