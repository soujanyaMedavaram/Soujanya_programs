#include<stdio.h>
#include<curses.h>
main()
{
	initscr();
	cbreak();
	printf("hello\n");
	nocbreak();
	endwin();
}
