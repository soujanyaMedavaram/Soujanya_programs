# include <curses.h>
main() {
	initscr() ;

	cbreak() ;
	addstr ("Press any character : " ) ;
	getch();
	refresh() ;
	nocbreak () ;
	endwin() ;
}
