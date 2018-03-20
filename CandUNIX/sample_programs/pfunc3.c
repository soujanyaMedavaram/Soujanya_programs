char a()
{
	printf ("a\n");
	return 'e';
}

char b()
{
	printf ("b\n");
	return 'f';
}

typedef char (*pfunc)();
typedef pfunc apfunc [];
apfunc c = { a, b };
apfunc *cc = &c;
char (*(*x) [] ) ();

apfunc * d()
{
	return cc;
}

main ()
{
	x = d();
	printf ("%c\n", (*(*(* x)[1] )) () );
}

