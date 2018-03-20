#include<stdio.h>
main(int argc, char *argv[])
{
int n,m,c,collect;
char *word;
char *malloc(int);
int pos;
if(argc!=3)
{
	fprintf(stderr,"Usage: a.out <width> <tabstop> \n");
	exit(1);
}
sscanf(argv[1],"%d",&n);
if( n < 10 || n > 70 )
{
	fprintf(stderr,"the limit of line length is 10  -  70");
	exit(2);
}
sscanf(argv[2],"%d",&m);
if( m < 2 || m > 10)
{
	fprintf(stderr,"tabstops in range 2,3...10\n");
	exit(3);
}
word = malloc(n + 1);
collect = 0;
pos=0;
while((c=getchar())!=EOF)
{
	if(c=='\n')
	{
		word[collect] = '\0';
		printf("%s\n",word);
		collect =0;
		pos=0;
		continue;
	}
	if(c == '\t')
	{
		do pos++;
		while(pos % m);
	}
	else pos++;
	if(pos >= n)
	{
		word[collect]='\0';
		printf("\n%s",word);
		pos=0;
		collect=0;
	}
	else if(c == ' ' || c== '\t')
	{
		word[collect] = '\0';
		printf("%s",word);
		collect=0;
	}
	word[collect++]=c;
}
if(collect)
{
	word[collect]='\0';
	printf("%s",word);
}
exit(0);
}
