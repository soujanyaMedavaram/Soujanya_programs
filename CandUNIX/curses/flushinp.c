#include<curses.h>
main()
{
	char  jyothi[31] ;
	initscr();
	flushinp();
	refresh();
	getstr(jyothi);
	endwin();
}	
