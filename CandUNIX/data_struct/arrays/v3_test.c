#include<stdio.h>

int *nums;
int *old;

main()
{
	int n, i, j;
	nums = (int *) malloc (sizeof(int));
	n = 0;
		for(j = 0; j < 5000; j++)
		{
			*(nums + n) = j;
		n++;
		old = nums;
		nums = (int *) malloc((n+1)*sizeof(int));
		for(i = 0; i < n; i++)
			nums[i] = old[i];

	}
	printf("\n The elements in the array are\n");
	for(i = 0; i < n; i++)
		printf("%d\t",nums[i]);
}
