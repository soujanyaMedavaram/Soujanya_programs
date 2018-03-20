#include<curses.h>
main()
{
	WINDOW * w1 , *w2;
	initscr();
	
	w1 = newwin(5,20,1,10);
	w2 = newwin(10,40,3,35);

	box(w1,'|','-');
	box(w2,'|','-');
	
	waddstr(w1,"hello window1");
	waddstr(w2,"hello window2");
	
	wnoutrefresh(w1);
	wnoutrefresh(w2);
	
	doupdate();
	wgetch(w2);

	endwin();
}
