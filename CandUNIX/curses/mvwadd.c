#include<curses.h>
main()
{
	WINDOW * win;
	initscr();
     clear();	
	box(stdscr,'|','-');
	mvwaddstr(stdscr,7,30,"-----------this is 10,30");
	mvwaddch(stdscr,8,30,'l');
	mvwaddch(stdscr,9,30,'v');
	wrefresh(stdscr);
	
	win = subwin(win,9,20,1,3);

	box(win,'|','-');
	wgetch(win);
	sleep(60);
	clear();
	endwin();
}
