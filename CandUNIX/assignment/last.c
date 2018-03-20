 # include <stdio.h>
 # include <stdlib.h>
 # include <string.h>
 
 main(int argc, char* argv[])
 {
 	FILE *fp;
	char s[20];
	int c, nlines, rest_lines, count = 0;
	int n;
	nlines = 0;
 	if(argc < 2)
	{
		fp = fopen("data12.dat","w");
		while ((c = getchar()) != EOF)
			putc(c,fp);
		strcpy(s , "data12.dat");
		fclose(fp);
		fp = fopen("data12.dat","r");
		n = 5;
	}
	else if (argc == 2)
	{
		if (*argv[1] == '-')
		{
			*++argv[1];
			n = atoi(argv[1]);
			fp = fopen("data12.dat","r");
			strcpy(s , "data12.dat");
		}
		else
		{
			fp = fopen(argv[1],"r");
			sscanf(argv[1],"%s",s);
			n = 5;
		}
	}
	else if(argc == 3)
	{
		*++argv[1];
		n = atoi(argv[1]);
		sscanf(argv[2],"%s",s);
		fp = fopen(argv[2],"r");
		if(fp == NULL)
		{
			printf("\n file can not be opened\n");
			exit(2);
		}
	}
	else
	{
		printf("\nUsage:<a.out> <-n><filename>\n");
		exit(1);
	}
	while((c = getc(fp)) != EOF)
	{
		if (c == '\n')
			nlines++;
	}
	fclose(fp);
	rest_lines = nlines - n;
	fp = fopen(s,"r");	
	while((c = getc(fp)) != EOF)
	{
		if  (c == '\n')
			count++;
		if(count >= rest_lines)
			putchar(c);
	}
}
		
