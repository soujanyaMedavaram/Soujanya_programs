#include<stdio.h>
#define HUGE 20

int nmax, place, n, i;
int total = 0, mean = 0, max = 0, min , abs_value = 0;
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

	/* (a) total,maximum, minimum of numbers */
	min = nums[0];
	for( i = 0; i < nmax; i++)
	{
		if(nums[i] > max)
			max = nums[i];
		if(nums[i] < min)
			min = nums[i];
		if (abs(nums[i]) > abs_value)
			abs_value = abs(nums[i]);
		total += nums[i];
	}
	printf( " The total of numbers is %d\n",total);

	/* (b) arithmetic mean of numbers */
	mean = total / nmax;
	printf(" The arithmentic of numbers is %d \n",mean);

	printf( "The maximum of numbers is %d \n",max);
	printf( "The minimum of numbers is %d \n",min);
	printf( "The maximum absolute value is %d ", abs_value);

}
