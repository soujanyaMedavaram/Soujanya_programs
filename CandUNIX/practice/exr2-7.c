# include <stdio.h>

unsigned getbits(unsigned, int ,int);

main()
{
	unsigned  x = 10;
	x = getbits(x,3,2);
	printf ("the value of X is %u \n",x);
}

unsigned getbits(unsigned x, int p, int n)
{
	return ~(x >> (p + 1 - n)) & ~(~0 << n);
}
