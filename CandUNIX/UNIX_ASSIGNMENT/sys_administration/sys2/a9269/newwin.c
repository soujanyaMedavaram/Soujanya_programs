# include <curses.h>

main () {
	WINDOW *w1, *w2 ;

	initscr () ;
	w1 = newwin ( 2,6,0,3 ) ;
	w2 = newwin ( 1,20,1,50 ) ;
	waddstr ( w1,"Uttara" ) ;
	waddstr ( w2,"Software Academy" ) ;
	wnoutrefresh ( w1 );
	wnoutrefresh ( w2 );
	doupdate () ;
	endwin () ;
}

