# include <curses.h>

# define MAX		100
# define full()		( sp == MAX )
# define empty()	( sp == 0 ) 
# define height		4

main () {
	WINDOW * disp, * uif, * visual, * uif_sub, * visual_subwin;
	char number [ 80 ], *p ;
	int  stack [MAX], val;
	int  sp;

	initscr () ;
	sp = 0;
	uif    = newwin ( 6, 45, 15, 1  );
	visual = newwin ( height + 2, 20, 1, 55 );
	box ( uif, 0, 0    );
	box ( visual, 0, 0 );
	uif_sub = subwin ( uif, 4, 43, 15, 2 ) ;
	wattrset ( uif_sub, A_BOLD ) ;
	mvwaddstr( uif_sub, 1, 1, "<num> to push; <p> to pop; <e> to exit" ) ;
	wrefresh ( uif ) ;
	wrefresh ( uif_sub ) ;
	wrefresh ( visual ) ;
	visual_subwin = newwin ( height, 18, 2, 56 );
	scrollok ( visual_subwin, TRUE );
	while ( 1 ) {
		mvwgetstr ( uif_sub, 2, 1, number ) ;
		for ( p = number ; *p == ' ' || *p == '\t' ; ++p ) ;
		if ( *p == 'e' || *p == 'E' || !*p ) break;
		switch ( *p ) {
			case 'p' : case 'P' :
				if ( empty () ) {
					mvwaddstr ( uif_sub, 3, 1, "Stack is empty " );
					break ;
				}
				wscrl ( visual_subwin, 1 );
				val = stack [--sp];
				mvwaddstr ( uif_sub, 3, 1, "              " );
				mvwprintw ( uif_sub, 3, 1, "%d", val );
				if ( sp >= height )
					mvwprintw ( visual_subwin, height - 1, 0,
									"%d", stack [sp - height] );
				break;
			case '0' : case '1' : case '2' : case '3' : case '4' :
			case '5' : case '6' : case '7' : case '8' : case '9' :			
				val = atoi ( p );
				if ( full () ) {
					mvwaddstr ( uif_sub, 3, 1, "Stack is full " );
					break ;
				}
				wscrl ( visual_subwin, -1 );
				mvwprintw ( visual_subwin, 0, 0, "%d", val );
				stack [sp++] = val;
				mvwaddstr ( uif_sub, 3, 1, "Done          " );
				break ;
			default : break;
		}
		wmove ( uif_sub, 2, 1 ) ;
		wclrtoeol ( uif_sub );
		wrefresh ( uif_sub ) ;
		wrefresh ( visual_subwin ) ;
	}
	endwin () ;
}
