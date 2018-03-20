# include <stdio.h>
# include <string.h>

void print_number();

FILE *fp;
int c, i = 1;
int count_n, count_e, count_v;
main(int argc, char *argv[])
{
	char *opt;
	count_n = count_e = count_v = 0;
	opt = (char *)malloc(20);
	strcpy(opt , "NO");
	if(argc == 1 )
	{
		while(getchar() != EOF);
		exit(0);
	}

	if (argc > 1)
	{

		if(*argv[1] == '@')
		{
			fp = fopen(argv[2],"w");
			while ((c = getchar()) != EOF)
				putc(c,fp);
			fclose(fp);
			exit(0);
		}
		if( *argv[1] == '-')
		{
			*++argv[1];
			strcpy(opt,argv[1]);
			i = 2;				//for positioning argv
			--argc;
		}
		else i = 1;
	}		
	while(--argc > 0)
	{
			if ((fp = fopen(argv[i],"r")) == NULL)
			{
				printf("file can not be opened - %s\n\n",argv[i]);
				i++;
				continue;
			}
			i++;
			if((strcmp(opt,"NO")) == 0)
			{
				while((c = getc(fp)) != EOF)
				putchar(c);
				continue;
			}
	while(*opt != '\0' && (strcmp(opt, "NO") != 0))
	{
		switch(*opt)
		{
			case 'n':
				count_n++;
				break;
			case 'e':
				count_e++;
				break;
			case 'v':
				count_v++;
				break;
			default:
				printf("\n use <man cat> command for help\n");
				exit(1);
		}
		opt++;
	}
	print_number();
	}
	putchar('\n');
	exit(0);
}

void print_number()
{
	int i = 1, verbose = 1, flag , count = 0;
	if (count_n == 1)
	printf("%d ",i++);
	while ((c = getc(fp)) != EOF)
	{
		if(count_n == 1 || count_e == 1)
			if(c != '\n' )
				putchar(c);
		if (c == '\n')
			flag = 0;
		if (c == '\n')
		{
			if (count_e == 1)
			{
				putchar('$');
				if(count_v == 0 && flag != 1)
				{
					flag = 0;
					count = 1;
					putchar(c);
				}
			}
			if (count_n == 1)
			{
				if(count_v == 0 && flag != 1 && count == 0)
				{
					flag = 0;
					putchar(c);
				}
				if(count_v != 1)
				{
					printf("%d ",i);
					i++;
				}
			}
		}
			if (count_v == 1)
			{
				if (c < ' ' && verbose && c != '\n')
				{
					putchar('^');
					putchar(c+0x40);
					if(count_n == 1)
					{
						printf("%d ",i);
						i++;
					}
				}
				else if(count_v == 1 && (count_n == 0 && count_e == 0))
				putchar(c);
			}
			//else putchar(c);
	}
}

/*void print_dollar()
{

	while ((c = getc(fp)) != EOF)
	{
		if (c == '\n')
			putchar('$');
		putchar(c);
	}
}

void print_verbose()
{
	int verbose = 1;
	while ((c = getc(fp)) != EOF)
	{
		if(c < ' ' && verbose)
		{
			putchar('^');
			putchar(c+0x40);
		}
		else
		putchar(c);
	}
}*/
