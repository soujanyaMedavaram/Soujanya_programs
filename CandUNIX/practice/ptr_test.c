# include <stdio.h>
main()
{
	int *p, a;
	//a = 5;
	//p = &a;
	*p = 6;
	printf ("p = %d\n",p);
	printf ("*p = %d\n",*p);
	printf ("&a = %d\n",&a);
}

