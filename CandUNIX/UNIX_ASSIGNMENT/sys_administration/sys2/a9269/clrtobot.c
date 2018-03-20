# include <curses.h>

main() {
	initscr () ;
	addstr ( "Extendexd Terminal Interface\n Again do this \n") ;
	move ( 1, 0 ) ;
	getch () ;
	clrtobot() ;
	refresh() ;
	endwin() ;
}
