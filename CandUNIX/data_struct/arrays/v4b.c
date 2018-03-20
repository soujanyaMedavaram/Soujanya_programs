#include<stdio.h>
//#include "v4space.c"

extern int nmax;
extern int nums[];

main()
{
	int i, n;
	printf( "\n enter the no. of elements \n");
	scanf( "%d", &n);
	if( n < 1 || n > nmax)
	{
		fprintf(stderr, "no of elements range is 1 - 20");
		exit(1);
	}

	printf("\n enter the elements \n");
	for ( i = 0; i < n; i++)
		scanf( "%d", &nums[i]);

	printf("\n the elements in the array are \n");
	for( i = 0 ; i < n; i++)
		printf("%d\t",nums[i]);
}
