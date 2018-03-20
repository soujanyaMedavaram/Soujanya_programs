# include <stdio.h>

main()
{
	char s[20];
	printf ("\n enter the string\n");
	while(1)
	{
		scanf("%s",s);
		switch(s)
		{
			case "hai": printf("\n switch hai\n");
			break;
			case "hello": printf("\n switch hello\n");
			break;
		}
	}
}
