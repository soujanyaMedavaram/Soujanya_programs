# include <stdio.h>

main()
{
	int i;
	for (i = 97; i < 97 + 26; i++)
	{
		printf ("\\%c\t",i);
		if ( i == 97)
			printf ("alert bell \n");
		else if (i == 98)
			printf ("back space\n");
		else if ( i == 102)
			printf ("form feed\n");
		else if ( i == 110)
			printf ("new line\n");
		else if ( i== 114)
			printf ("carriage return\n");
		else if ( i == 116)
			printf ("horizontal tab\n");
		else if ( i == 118)
			printf ("vertical tab\n");
		else
			printf ("\n");
	}
	printf ("\\\tback slash\n");
	printf ("\\?\tquestion mark\n");
	printf ("\\'\tdouble quote\n");
	printf ("\\ooo\toctal number\n");
	printf ("\\xhhh\thexadecimal number\n");
}

