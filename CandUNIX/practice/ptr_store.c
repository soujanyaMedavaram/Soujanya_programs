# include <stdio.h>

main()
{
	int *a, **b;
	int c[10][10];
	int i,j;
	for (i = 0; i <10; i++)
		for(j =0; j < 10; j++)
			c[i][j] = i+ j;
	a = &c[0][0];
	//b = &c[0][0];
}
