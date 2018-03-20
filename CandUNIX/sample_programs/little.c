# include <stdio.h>

main ()
{
	int x = 1;

	if (*(char *)&x == 1)
		printf ("Little Endian\n");
	else
		printf ("Big Endian\n");
}
