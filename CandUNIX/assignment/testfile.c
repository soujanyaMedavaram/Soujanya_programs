# include <stdio.h>

main()
{
	char s[] = "data.dat";
	FILE *fp;
	fp = fopen(s,"r");
	if (fp == NULL)
		printf("file can not be opened\n");
	else printf("file opened\n");
}
