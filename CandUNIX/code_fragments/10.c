# include <stdio.h>
main()
{
	int i = 0, c;
	while(c = getchar() != EOF)
	{
		i++;
	}
	printf ("i = %d\n",i);
}
