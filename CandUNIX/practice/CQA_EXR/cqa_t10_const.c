# include <stdio.h>

main ()
{
	const int a = 5;
	int b = 25;
	int *p = &b;
	const *ip = &b;
	ip = &a;
	*p = 10;
	*ip = 20;
}
