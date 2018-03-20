# include <stdio.h>

main(int argc, char *argv[])
{
	FILE *fp;
	if(argc < 2)
	{
		if ((fp = fopen("/etc/passwd","r")) == NULL)
		{
			fprintf(stderr,"file cant be opened\n");
			exit(1);
		}
		read_file(fp);
		close(fp);
		exit(0);
	}

	while(*++argv)
	{
		if ((fp = fopen(*argv,"r")) == NULL)
		{
			printf("cannnot open file\n");
			exit(2);
		}
		printf("\n file is - %s\n",*argv);
		read_file(fp);
		close(fp);
	}
	exit(0);
}
int read_file(FILE *fp)
{
	int c;
	while ( (c = getc(fp)) != EOF)
	{
		putchar(c);
	}
}
