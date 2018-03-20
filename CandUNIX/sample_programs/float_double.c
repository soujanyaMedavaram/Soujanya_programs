# include <stdio.h>

main ()
{
	int a;
	int fun (float);
	int fun1 (double);

	a = fun (3.14);
	printf ("%d\n",a);
	a = fun1 (3.14);
	printf ("%d\n", a);
}

int fun (float aa)
{
	printf ("aa = %f\n",aa);
	return aa;
}

int fun1 (float aa)
{
	printf ("aa = %f\n",aa);
	return aa;
}
