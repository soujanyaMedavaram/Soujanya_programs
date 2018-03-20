# include <stdio.h>
main()
{
	int num;
	while(1)
	{
		printf ("\n enter a number \n");
		scanf ("%d",&num);
		switch(num % 10)
		{
			case 1: printf("one\n");
			case 2: printf("two\n");
			case 3: printf("three\n");
		}
	}
}
	
