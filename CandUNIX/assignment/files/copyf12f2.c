#include<stdio.h>

main()
{
	FILE *fp1, *fp2;
	int c;
	fp1 = fopen("test1.dat","r");
	fp2 = fopen("test2.dat","w");	
	printf("the contents of file1 are \n");
	while ( (c = getc(fp1)) != EOF )
	{
		putc( c, fp2);
		putchar(c);
	}
	fclose(fp2);
	fclose(fp1);
	printf( "The contents of file 2 are \n");
	fp2 = fopen("test2.dat","r");
	while ( (c = getc(fp2)) != EOF )
		putchar(c);
	
	fclose(fp2);
}





