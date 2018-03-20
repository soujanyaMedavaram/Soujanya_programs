char a()
{
	putchar ('a');
}

char (*b) () = a;
main()
{
	(*b)();
	b();
	putchar ('\n');
}

