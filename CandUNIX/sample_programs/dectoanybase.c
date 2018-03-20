# include <stdio.h>

main()
{
	int base;
	unsigned int n;
	char digits[80];
	int i;
	unsigned int m;
	int flag;
	printf ("Enter base for conversion :");
	scanf ("%d", &base);
	if (base < 2 || base > 36) exit (3);
	while (1)
	{
		printf ("Enter a number (-1) to exit : ");;
		if (scanf ("%u",&n) < 1) exit(1);
		if ( n == 0xffffffff) exit(2);
		flag = 0;
		printf (":");
		i = 0;
		while (n)
		{
			m = n % base;
			digits[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[m];
			n /= base;
			i++;
		}
		for (i--; i >= 0;i--)
		{
			if (!flag && digits[i] != '0') flag = 1;
			if (flag) putchar (digits[i]);
		}
		printf (":\n");
	}
}
