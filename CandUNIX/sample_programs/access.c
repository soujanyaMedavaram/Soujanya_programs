#include <stdio.h>

main ()
{
	int *ptr;
	int xyz = 12345;
	int array[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	ptr = &array[0][0];
	printf("ptr - %u\n",ptr);
	sub (array, array, array, array, array, &ptr);
}

sub (int *a, int (*b)[4], int (*c)[7], int d[][4], int e[][3], int **q)
{
	printf ("a = %u b = %u c = %u d = %u e = %u\n",(unsigned) a,(unsigned) b, 
	(unsigned) c, (unsigned) d, (unsigned) e);

	printf ("Values : %d %d %d %d %d\n", *a,(*b)[0], (*c)[0],d[0][0],
	e[0][0]);

	printf ("c[0] : [0] = %d [1] = %d [2] = %d\n",(*c)[0], (*c)[1],
	(*c)[2]);

	printf ("c[1]: [0] = %d [1] = %d [2] = %d \n",c[1][0],c[1][1],c[1][2]);

	a++,b++,c++,d++,e++;
	
	printf ("a = %u b = %u c = %u d = %u e = %u\n",(unsigned)a, (unsigned)b,
	(unsigned)c, (unsigned)d, (unsigned)e);

	printf ("Values : %d %d %d %d %d\n", *a, (*b)[0], (*c)[0], d[0][0],
	e[0][0]);

	printf ("c[1] : [0] = %d [1] = %d [2] = %d\n", (*c)[0], (*c)[1], (*c)[2]);

	printf ("c[1] : [3] = %d [4] = %d [5] = %d\n",(*c)[3], (*c)[4], (*c)[5]);

	printf ("c[1] : [6] = %d [7] = %d [8] = %d\n",(*c)[6], (*c)[7], (*c)[8]);

	printf ("c[1] : [9] = %d [10] = %d [11] = %d\n", (*c)[9], (*c)[10], 
	(*c)[11]);

	printf ("c[0] : [0] = %d [1] = %d [2] = %d\n", c[-1][0],c[-1][1],c[-1][2]);
	printf ("q = %u *q = %u **q = %d\n", (unsigned) q, (unsigned)  *q, **q);

	printf ("q : [0] = %d [1] = %d [2] = %d\n", (*q)[0], (*q)[1],(*q)[2]);

	++*q;
	printf ("q : [0] = %d [1] = %d [2] = %d\n",(*q)[0], (*q)[1],(*q)[2]);
	printf ("q = %u *q = %u **q = %d\n",(unsigned)q, (unsigned) *q, **q);
}


