#include<stdio.h>
#define max(a,b) ((a) > (b) ? (a):(b))
main() {
	int a,b;
	printf("\n Enter any two integers:");
	scanf("%d%d",&a,&b);
	a=max(a,b);
	printf("MaximUm of the two numbers is %d :",a);
		}
