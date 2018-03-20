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

char (*c[]) () = {a, b};
char (*(*x() )[] ) ()
{
	return &c;
}

main()
{
	printf ("%c\n", (*(*(* x()) [1] )) () );
	printf ("%c\n", (*(* x()) [1] ) () );

}
