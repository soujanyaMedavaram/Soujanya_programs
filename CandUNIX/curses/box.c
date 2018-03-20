#include<curses.h>
main()
{
	WINDOW * win;
	initscr();
	win = newwin(5,20,1,30);
	box(win,'|','-');
	wrefresh(win);
	wgetch(win);
	endwin();
}
