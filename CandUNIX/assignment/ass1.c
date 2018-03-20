#include<stdio.h>
main()
{
	char ch;
	while((ch=getchar())!=EOF)
	{
		if(ch>40)
		{
			printf("character is %c",ch);
		}
	}
}
