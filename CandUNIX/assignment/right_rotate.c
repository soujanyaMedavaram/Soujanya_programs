#include<stdio.h>
int right_rotate(int x,int n);
main()
{
	int x,n;
	printf("\n enter aan integer\n");
	scanf("%d",&x);
	printf("\n enterrotatate number\n");
	scanf("%d",&n);
	x=right_rotate(x,n);
	printf("\n the rotated number is %d",x);
}

int right_rotate(int x, int n)
{
	int mask=1<<(sizeof(int)*8-1);
	int lsb;
	while(n--)
	{
		lsb = x&1;
		x >>=1;
		if(lsb) x|= mask;
	}
	return x;
}
