# include <stdio.h>
main()
{
	int i = 4, j = 5;
	int x = i && j;
	printf ("x = %d\n",x);
	i = 0;
	x = i && j;
	printf ("x = %d",x);
}
