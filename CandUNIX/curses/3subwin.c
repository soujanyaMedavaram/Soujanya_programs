#include<curses.h>
main()
{
	WINDOW * w1 , *w2 , *win;
	initscr();
	
	win = newwin(20,30,1,10);
	w1 = subwin(win,16,25,3,12);
	w2 = subwin(win,12,19,5,15);

	box(win,'|','-');
	box(w1,'|','-');
	box(w2,'|','-');
	wrefresh(win);
	wrefresh(w1);
	wrefresh(w2);
	wgetch(w2);
	endwin();
}
