/* atof to handle 123.45e-6 */
# include <stdio.h>

# include <ctype.h>

double atof(char s[])
{
	double val, power;
	int exp, i, sign;

	for ( i = 0; isspace(s[i]);i++);
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	val = sign * val / power;

	if (s[i] == 'e' || s[i] == 'E')
	{
		sign = (s[++i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (exp = 0; isdigit(s[i]); i++)
			exp = 10 *exp + (s[i] - '0');
		if (sign == 1)
			while (exp-- > 0)
				val *= 10;
		else
			while (exp-- > 0)
				val /= 10;
	}
	return val;
}

main ()
{
	char line[100], *p;
	double value;
	printf("\n enter the notation\n");
	fgets(line,100,stdin);
	for ( p = line ; *p == ' ' || *p == '\t'; p++);
	value = atof(p);
	printf("the value is %lf\n",value);
}
