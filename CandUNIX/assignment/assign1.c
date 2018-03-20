	/* printig the characters more than 40*/
	
	#include<stdio.h>
	main()
{
	int c;
	while((c = getchar()) != EOF)
	{
		if(c > 40)
		putchar(c);
		putchar('\n');
	}
}
