#include <curses.h>

main() {
	initscr() ;

	move ( LINES / 2  , COLS / 2 - 4 );
	addstr ( "BULLS" ) ;
//	refresh () ; // ETI pgm does not otpt to a window until refresh is called
	addstr ( "EYE" ) ;
	refresh () ;
	endwin () ; /* Restores all terminal settings and positions the cursor at 
				 the lower left corner of the screen. */
}
	
