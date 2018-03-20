  char * mem_io;

sub ()
{
	mem_io = (char *) 0xFFE00000;
	while (*mem_io & 0x01);
}
main()
{
	sub();
}
