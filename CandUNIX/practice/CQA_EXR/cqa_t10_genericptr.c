# include <stdio.h>
main()
{
	int *x,a = 10;
	double *y,b = 6.5;
	void *z;
	z = &a;
	printf ("Z = &a and *zis %d\n",*(int *)z);
	z = &b;
	printf ("Z = &b and *z is %d",*(int *)z);
}
