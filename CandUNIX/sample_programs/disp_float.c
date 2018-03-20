# include <stdio.h>

typedef float type;

void fdisplay (type x);
void binary (unsigned char x, int pos);

main ()
{
	fdisplay (1.0);
	fdisplay (2.0);
	fdisplay (3.0);
	fdisplay (3.5);
	fdisplay (4.0);
	fdisplay (8.0);
}

void fdisplay (type x)
{
	unsigned char *p = (unsigned char *) (&x + 1);
	int i;
	printf ("%2.2f:",x);
	for (i = 0; i < sizeof (type); i++)
	{
		binary (*--p, i);
		putchar (' ');
	}
	putchar ('\n');
}
void binary (unsigned char x, int pos)
{
	int i;
	unsigned char mask = 0x80;
	for ( i = 0; i < 8; i++)
	{
		if (x & mask) putchar ('1');
		else putchar ('0');
		if (pos == 1 && i == 4) putchar (' ');
		mask >>= 1;
	}
//	putchar (' ');
}
