# include <stdio.h>
# include <curses.h>

main ( ) {
	WINDOW * sub;
	int row = 7, col = 18;

	//printf ( "\n enter the width and height of the box \n" );
//	scanf ( "%d%d", &col, &row );
	initscr( );
	sub = subwin ( stdscr, 6, 18, 1, 1 );
	box ( sub, ACS_VLINE, ACS_HLINE );
	mvwaddstr ( sub, 1, 1, " NAME Roll No. " );  
	wnoutrefresh (sub);
	sub = subwin ( stdscr, 3, 20, 1, 18 );
	box ( sub, ACS_VLINE, ACS_HLINE );
	mvwaddstr ( sub, 1, 1, " MARKS OBTAINED " );  
	wnoutrefresh (sub);
	doupdate ( );
	endwin ( );
}
