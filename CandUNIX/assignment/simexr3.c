#include<stdio.h>
main()
{
	int c,flag=0;
	while((c=getchar())!=EOF)
	{
		if(c==' ')
		{
			if(!flag)
			{
				flag=1;
				putchar(c);
			}
		}
		else
		{
			flag=0;
			putchar(c);
		}
	}
}

