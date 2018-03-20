# include <stdio.h>
main(int argc, char *argv[])
{
	printf("%s=*argv\n",*argv);
	printf("%s=*++argv\n",*++argv);
	printf("%s=*argv\n",*argv);
	printf("%s=++*argv\n",++*argv);
}
