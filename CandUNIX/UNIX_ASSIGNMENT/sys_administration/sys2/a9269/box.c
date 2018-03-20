# include <curses.h>

main () {
	WINDOW * sub ;
	
	initscr () ;
	box ( stdscr, '+','-') ;
	mvwaddstr( stdscr,7,10,"This is at 7,10") ;
	mvwaddch ( stdscr,8,10,'|') ;
	mvwaddch ( stdscr,9,10,'v') ;
	sub = subwin ( stdscr, 10, 20, 10, 10 ) ;
	box ( sub, 's', '*' ) ;
	wnoutrefresh ( stdscr ) ;
	wnoutrefresh ( sub ) ;
	doupdate ( ) ;
	endwin () ;
}

//home/uttara/audio43/a9269/ETI
