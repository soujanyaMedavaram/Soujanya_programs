#include<stdio.h>

main()
{
	FILE *fp1,*fp2;
	char a[50][50],string[50];
	int i, place = 0;
	fp1 = fopen("test1.dat","r");
	fp2 = fopen("test2.dat","w");
	while ( (fgets(string,50,fp1)) != NULL )
	{
		strcpy(a[place++],string);

	}

	for (i = place - 1; i >= 0; i--)
	{
		fputs(a[i],fp2);
	}
}
