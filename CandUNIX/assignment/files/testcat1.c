# include <stdio.h>
main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	fp = fopen(argv[1],"w");
	while((c = getchar()) != EOF)
		putc(c,fp);
	fclose(fp);
	fp = fopen(argv[1],"r");
	while((c = getc(fp)) != EOF)
		putchar(c);
	printf("\n program end\n");
}
