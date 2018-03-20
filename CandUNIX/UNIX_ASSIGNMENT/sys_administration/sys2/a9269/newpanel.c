# include <panel.h>

main () {
	WINDOW *win ;
	PANEL *pptr ;

	initscr () ;
	win = newwin ( 3,20,0,3 ) ;
	box (win,0,0) ;
	wmove (win,1,3) ;
	waddstr ( win,"This is at 1,3" );// x and y wrt window instead of screen crd
	pptr = new_panel (win) ;
	wnoutrefresh( win ) ;
	doupdate () ;
	endwin () ;
}
	

