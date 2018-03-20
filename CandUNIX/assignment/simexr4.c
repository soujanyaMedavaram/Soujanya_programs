/*  detab.c */

#include<stdio.h>
main(int argc, char *argv[])
{
	int n,c,col;
	if(argc != 2)
	{
		fprintf(stderr, "Usage: a.out <tabstop>\n");
		exit(1);
	}
	sscanf(argv[1],"%d",&n);
	if(n<2 || n>10)
	{
		fprintf(stderr,"tabstops in range 2,3...10\n");
		exit(2);
	}
	col=0;
	while((c=getchar())!=EOF)
	{
		if(c == '\t')
		{
			do
			{
				putchar(' ');
				col++;
			}while(col%n);
		}
		else
		{
			putchar(c);
			if(c == '\n') col=0;
		}
	}
}
