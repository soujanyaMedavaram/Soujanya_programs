# include <curses.h>

main ( ) {
	initscr ( ) ;
	addch ('a') ;
	refresh ( ) ;
	endwin ( ) ;
}
