#include<stdio.h>
main()
{
	struct x
	{
		char c;
		int i;;
	}abc;
	printf("%u %u\n",&abc.c,&abc.i);
}
