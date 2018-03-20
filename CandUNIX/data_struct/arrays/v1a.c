#include<stdio.h>
#define NMAX 10

double nums[NMAX];

main()
{
	int place, n;
	place = 0;
	while ( place < NMAX )
		if ( scanf ( "%lf", &nums[place]) == 1 )
			place++;
		else break;
	if (!place)
	{
		fprintf(stderr,"beserious\n");
		exit(1);
	}


	n = place;
	for( place = 0; place < n; place++)
	printf( "%6.2lf\t", nums[place]);
	exit(0);
}
