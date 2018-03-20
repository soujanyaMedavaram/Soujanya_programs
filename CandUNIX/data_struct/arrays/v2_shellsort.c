#include<stdio.h>
#define HUGE 100

void shellsort ( int *, int);

int nmax, i;
int *nums;

main()
{
	printf( "\n enter the no. of elements\n" );
	while ( scanf( "%d", &nmax ) != 1 )
	{
		fprintf( stderr, "wrong input" );
		exit(1);
	}

	if ( nmax < 1 && nmax > HUGE )
	{
		fprintf( stderr, "size range is 1...100" );
		exit(2);
	}
	nums = (int *)malloc(nmax * sizeof(int));
	printf("\n enter the elements \n");
	for ( i = 0; i < nmax; i++)
		scanf( "%d", &nums[i]);

	/* shell sorting */
	shellsort(nums,nmax);

	printf( "\n The elements in ascending order are \n" );
	for ( i = 0; i < nmax; i++)
		printf( "%d", nums[i]);
}

/* definition of shell sort */
void shellsort ( int *nums, int nmax )
{
	int gap, j, temp;
	for ( gap = nmax / 2; gap > 0; gap /= 2)
		for ( i = gap; i < nmax; i++)
			for ( j = i - gap; j >= 0 && nums[j] > nums[j + gap]; j -= gap)
			{
				temp = nums[j];
				nums[j] = nums[j + gap];
				nums[j + gap] = temp;
			}
}

	
