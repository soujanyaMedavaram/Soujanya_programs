# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main(int argc, char *argv[])
{
	int fp;
	char s[25];
	if(argc < 2)
	{
		strcpy(argv[1],"/etc/passwd");
		fp = open(s,O_RDONLY);
		read_file(fp);
		close(fp);
		exit(1);
	}

	while(*++argv)
	{
		fp = open(*argv,O_RDONLY);
		printf("\n file - %s\n",*argv);
		read_file(fp);
		close(fp);
	}
	exit(0);
}
read_file(int fp)
{
	char c;
		if (fp == -1)
		{
			printf("cannnot open fikle\n");
			exit(1);
		}
		while(read(fp,&c,sizeof(c)))
			putchar(c);
}
