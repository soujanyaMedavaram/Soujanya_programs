# include <stdio.h>

# define MAX_DIGITS	10

void permute (char *digits, int ndigits, char *pre, int npre);
char *malloc (int);

main ()
{
	int n; char digits[MAX_DIGITS];
	int ndigits; char *pre;

	printf ("enter a number :");
	scanf("%d",&n);
	if (n < 0) n = -n;
	sprintf (digits, "%d", n);
	ndigits = strlen (digits);
	pre = NULL;
	permute (digits, ndigits, pre, 0);
	putchar('\n');
}

void permute (char *digits, int ndigits, char *pre, int npre)
{
	int i, j;
	char *dig, *p;
	char *prefix; int nprefix;

	if (ndigits == 1)
	{
		if (pre == NULL)
			printf ("%c\n", digits[0]);
		else
			printf ("%s%c\t",pre,digits[0]);
		return;
	}

	for ( i = 0; i < ndigits; i++)
	{
		dig = malloc (ndigits - 1);
		for ( p =dig, j = 0; j < ndigits; j++)
			if (j != i) *p++ = digits[j];
		nprefix = npre + 1;
		prefix = malloc (nprefix);
		strncpy (prefix, pre, npre);
		prefix[nprefix - 1] = digits[i];
		permute (dig, ndigits -1, prefix, nprefix);
		free (dig);
	}
}

