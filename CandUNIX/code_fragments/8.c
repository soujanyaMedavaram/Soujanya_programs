# include <stdio.h>
main()
{
	char a[] = "hello";
	int i;
	i = strlen(a);
	printf ("strlen of a is %d\n",i);
	i = sizeof(a);
	printf ("size of a is %d\n",i);
}
