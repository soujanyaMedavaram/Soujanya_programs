# include <stdio.h>

main () {
	int num, i = 0, rem;
	char b[20];
	char a[] = { '0', '1', '2', '3', '4', '5', '6', '7', 
	'8', '9', 'a', 'b', 'c','d', 'e', 'f' };

	printf ( "\n enter a number \n");
	scanf (" %d",&num);
	printf ("\n hex no : %x",num);
	while ( num )
	{
		rem = num % 16;
		b[i++] = a[rem];
		num = num / 16;
	}
	printf ("\n computed hex no is \n");
	while (i)
		printf ("%c",b[--i]);
}

