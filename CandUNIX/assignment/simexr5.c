#include<stdio.h>
main(int argc, char *argv[])
{
	int n,c,in_pos,out_pos;
	in_pos=out_pos=0;
	sscanf(argv[1],"%d",&n);
	while((c = getchar()) != EOF)
	{
		if(c=='\n')
		{
			putchar(c);
			in_pos=out_pos=0;
			continue;
		}
	if(c == ' ') in_pos++;
	else if(c == '\t')
	{
		do in_pos++;
		while(in_pos%n);
	}
	else
	{
		while(out_pos < (in_pos / n * n))
		{
			putchar('\t');
			do out_pos++;
			while(out_pos % n);
		}
		while(out_pos < in_pos)
		{
			putchar(' ');
			out_pos++;
		}
		putchar(c);
		in_pos++;
		out_pos++;
	}
}exit ( 0 );
}
