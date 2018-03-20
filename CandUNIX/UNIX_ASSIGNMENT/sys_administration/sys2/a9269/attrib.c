# include <curses.h> 

main() {
	initscr ( ) ;
	printw("This is the normal mode\n" ) ;
	attrset(A_BOLD) ;
	printw("This is the bold mode\n" ) ;
	attrset(A_BOLD | A_UNDERLINE ) ; 
	printw("This is the bold and underline mode\n" ) ;
	attrset(A_STANDOUT ) ; 
	printw("This is the standout mode\n" ) ; 
	refresh() ;
	attrset (0) ;
	endwin() ;
}
