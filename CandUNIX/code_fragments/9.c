# include <stdio.h>
main()
{
	char a[10] = "hello";
	int i;
	for ( i = 0; i < 10; i++)
	{
		printf ("%c",a[i]);
		if(a[i] == '\0')
			printf("null");
	}
}
