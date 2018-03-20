# include <curses.h>

main() {
	initscr () ;
	printw ("After moving cursor should be here") ;
	printw ("\n\n\n\n") ;
	move (0,28) ;
	refresh () ;
	getch() ;
	endwin() ;
}
