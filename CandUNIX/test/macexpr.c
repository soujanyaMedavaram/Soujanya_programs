/* macros with expr statement */

#include<stdio.h>
#define dprint(expr) printf(#expr"=%d\n",expr)
main()
{
	int x=20,y=10,z;
	z=dprint(x/y);
}
