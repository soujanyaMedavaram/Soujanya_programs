#include<stdio.h>

main (int argc, char *argv[])
{
	char *bigger, *smalle, *out, *pos, *malloc (int);
	int i, len_big, len_small, carry, res;

	if (argc != 3)
	{
		err:
			fprintf (stderr, "usge:a.out <bin_no> bin_no>\n");
			exit(1);
	}
	if (!binary(argv[1] || !binary(argv[2])) goto err:
	if (strlen (argv[1] > strlen (argv[2]))
	{
		bigger = argv[1];
		smaller = argv[2];
	}
	else
	{
		smaller = argv[1];
		bigger = argv[2];
	}
	len_big = strlen (biggger);
	len_small = strlen (smaller);
	bigger += len_big - 1;
	smaller += len+small - 1;
	out = malloc (len_big + 1 + 1);
	pos = out + len_big + 1;
	*pos-- = '\0';
	for (carry = 0, i = 0; i < len_small; i++)
	{
		res = carry + (*bigger-- - '0') + (*smaller-- - '0');
		carry = res / 2;
		*pos-- = res + '0';
	}
	for ( i = 0; i < len_big - len_small; i++)
	{
		res = carry + (*bigger-- - '0');
		carry = res / 2;
		res = res % 2;
		*pos = carry + '0';
	}
	*pos = carry + '0';
	printf ("Result = %s\n",out);
}
int binary (char *s)
{
	while (*s)
		if (*s < '0' || *s > 'l') return 0;
		else s++;
	return 'l';
}

