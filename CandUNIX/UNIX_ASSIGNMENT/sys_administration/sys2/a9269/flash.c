# include <curses.h>

main() {
	
	initscr() ;
	printw ( "%d\n",flash() ) ;
	printw ( "Uttara" ) ;
	refresh() ;
	endwin() ;
}
