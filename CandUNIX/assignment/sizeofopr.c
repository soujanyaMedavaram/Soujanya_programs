#include<stdio.h>

main()
{
	int x,i;
	int bin = 0, rem;
	printf("enter an element\n");
	scanf("%d",&x);
	i = 0;
	while ( x > 0 ) {
		rem = x % 2;
		bin = (bin *10)+ rem;
		x = x/2;
	}
	for(i=0;bin!=0;i++)
	bin = bin<<1;
	printf("size id %d",(i/8));
	printf ( "\nsizeof int %d\n", sizeof(int));
}
