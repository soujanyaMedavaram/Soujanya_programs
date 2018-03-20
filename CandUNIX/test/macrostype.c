/* programs for macros */

#include<stdio.h>
#define max(a,b) ((a) > (b) ? (a) : (b))
main()
{
	int x,y,sum1,sum2;
	x=10;
	y=20;
	sum1=max(x+1,y+1);
	printf("\n result of x+1 and y+1 is %d",sum1);
	sum2=max(x++,y++);
	printf("\n result if x++ and y++ is %d",sum2);
}

