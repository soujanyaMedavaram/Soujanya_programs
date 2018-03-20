#include<curses.h>
main()
{
	WINDOW * win;
	initscr();
	win = newwin(5,20,1,30);
	waddstr(win,"hello window");
	wrefresh(win);
	wgetch(win);
	endwin();
}
