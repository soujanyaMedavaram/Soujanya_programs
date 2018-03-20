#include<curses.h>
main()
{
	WINDOW * w1,*w2 ;
	initscr();
	w2=newwin(10,10,10,10);
	
	w1 = subwin(w2,20,10,10,20);

	box(w1,'|','-');
	wrefresh(w2);
	wrefresh(w1);
	wgetch(w1);
	endwin();
}
