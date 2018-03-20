# include <stdio.h>
# include <curses.h>

main ( ) {
	//curs_initscr ( );
	newterm(NULL, stdout, stdin );
	cbreak( );
	noecho( );
	move( 10, 10 );
	refresh( );
	printf ( "hai" );
	endwin( );
}
