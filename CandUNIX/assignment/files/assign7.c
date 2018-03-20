# include <stdio.h>

main()
{
	int c = 'a',flag,i;
	char str[1000];
	for ( i = 0; (c = getchar()) != EOF; i++)
		str[i] = c;
	for(i = 0; i < strlen(str); i++)
	{
	if ((c = str[i])!= '\0')
	{
		if (c == '/')
		{
			c = str[++i];	
			if (c == '*')
			{
				c = str[++i];
				flag = 1;
			}
			else 
				c = str[--i];
			if (c == '\n' || flag == 1)
				printf("//");
			//putchar(c);
		}
		else if (c == '*')
		{
			c = str[++i];
			if (c == '/')
			{
				flag = 0;
				continue;
			}
			else
				c = str[--i];
		}
		if (c == '\n' && flag == 1)
		{
			putchar(c);
			printf("//");
		}
		else 
			putchar(c);
	}
	}

}


	

