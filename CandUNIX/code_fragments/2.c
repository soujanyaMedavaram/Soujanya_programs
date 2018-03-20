# include <stdio.h>

main()
{
	int i;
	for ( i = 0; ; i++)
	{
		i = i +2;
		continue;//break;
		printf("%d",i);
	}
}
