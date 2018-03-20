#include<stdio.h>
main() {
	int *a,b=10;
	a=&b;
	printf("\n *a is %d ",*a);
	printf("\n a is %u ",a);
	printf("\n &a is %u ",&a);
	printf("\n b is %d ",b);
	printf("\n &b is %u ",&b);
	printf("\n a = &b is %u = %u ",a,&b);
	}
