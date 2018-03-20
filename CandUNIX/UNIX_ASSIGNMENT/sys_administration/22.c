# include <stdio.h>
# include <curses.h>

main ( ) {
	int wid, hgt, i, j, k;
	WINDOW *win;
	printf ( "\n enter width and height \n" );
	scanf ( "%d%d", &wid, &hgt );
	newterm ( NULL, stdout,stdin );
	cbreak ( );
	noecho ( );
	move( 5,5 );
	refresh( );
	printf ( "hai" );
	box( stdscr, wid, hgt );
	endwin ( );
}
