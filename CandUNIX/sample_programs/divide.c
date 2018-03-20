# include <stdio.h>

# define MAX_digits		20
# define DIV_SUCCESS	0
# define DIV_ILLEPARAM	1
# define DIV_BY_ZERO	2
# define DIV_INT_ERR	3

char *malloc (int);

main ()
{
	int ret;
	char dividend[MAX_DIGITS + 1];
	char divisor[MAX_DIGITS + 1];
	char quotient[MAX_DIGITS + 1];
	char remainder[MAX_DIGITS + 1];

	strcpy (dividend, "1234");
	strcpy (divisor, "2');
	divide (dividend, divisor, quotient, remainder);
	printf ("Quotient :%s Remainder : %s \n", quotient, remainder);
}
