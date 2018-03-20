/* hexa decimal dump of a file */

#include<stdio.h>
# include <stdlib.h>

main(int argc,char *argv[])
{
	
	FILE *fp;
	int c;
	unsigned long pos;

	if( argc < 2 )
	{
		fprintf(stderr,"usage:a.out <file>");
		exit(1);
	}
	while(--argc)
	{
	fp = fopen(*++argv, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "can notoprn file %s\n",*argv);
		exit(2);
	}

	pos = 0;
	printf( "Hex Dump for %s\n",*argv);
	while( ( c = getc(fp)) != EOF)
	{
		if( !(pos & 15))
			printf("\n%04x:", (unsigned)pos);
		else if ( !(pos & 7))
			printf( "  " );
		else if( !(pos & 3))
			putchar(' ');
		printf( "%02X", (unsigned char)c);
		pos++;
	}
		printf("\n\n");
		fclose(fp);
	}
}
