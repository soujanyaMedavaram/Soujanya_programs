# include <curses.h>

main() {
	WINDOW *win;
	int i ;

	initscr();
	for ( i = 0; i < 80; i += 3 ){
		win = newwin ( 2, 2, 2, i ) ;
		box ( win, 0, 0 ) ;
		wrefresh ( win ) ;
		werase (win ) ;
		wrefresh ( win ) ;
		sleep (1) ;
		
	}
	endwin () ;
	
}

		

