#include<curses.h>
main()
{
	WINDOW * w1 , *w2;
	initscr();
	w1 = newwin(5,20,1,10);
	w2 = newwin(10,40,3,25);
	waddstr(w1,"hello window1");
	waddstr(w2,"hello window2");
		
	wrefresh(w1);
	wrefresh(w2);

	wgetch(w2);
	endwin();
}
