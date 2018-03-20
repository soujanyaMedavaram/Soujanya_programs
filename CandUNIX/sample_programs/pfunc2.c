char a(), b();
char (*c[]) () = { a, b};
char (*(*x) [] ) ();

main ()
{
	 x= &c;
	 printf ("%c\n",(*(*(*x)[1])) ());
}

char a()
{
	printf("a\n");
	return 'e';
}
char b()
{
	printf("b\n");
	return 'f';
}
