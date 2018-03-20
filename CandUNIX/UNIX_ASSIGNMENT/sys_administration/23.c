# include <stdio.h>
# include <curses.h>

main ( ) {
	WINDOW * sub;
	int row, col;

	printf ( "\n enter the width and height of the box \n" );
	scanf ( "%d%d", &col, &row );
	initscr( );
	sub = subwin ( stdscr, row, col, 1, 1 );
	box ( sub, ACS_VLINE, ACS_HLINE );
	wnoutrefresh (sub);
	doupdate ( );
	endwin ( );
}
