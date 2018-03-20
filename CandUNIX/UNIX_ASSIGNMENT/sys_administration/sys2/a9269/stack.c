# include <curses.h> 

# define MAX 		50
# define empty() 	( sp == 0  ) 
# define full()  	( sp == MAX )
# define type int

main () { 
	WINDOW *uif, *visual, *visual_sub, *disp;	
	char number [ 10  ] , *p ;
	type stack  [ MAX ] , val ;
	int sp, startx , starty;
	int i ;
	
	initscr ();
	sp =  0;
	startx = starty = 0 ;
	
	disp   = newwin ( 3, 10, 1, 25 );
	box (disp, 0, 0 ) ;
	wattrset ( disp, A_STANDOUT ) ;
	mvwaddstr ( disp, 1, 1 ,"  STACK "); 
	wrefresh ( disp);
	uif    = newwin ( 5, 43, 15, 1 );
	visual = newwin ( 10, 20, 1, 45 ) ;
	visual_sub = newwin ( 8, 15, 2, 46 ) ;
	box ( uif, 0, 0 ) ;
	box ( visual, 0, 0 ) ;
	wattrset ( uif, A_BOLD ); 
	mvwaddstr ( uif, 1, 1, "<num> to push ; <p> to pop; <e> to exit" ) ;
	scrollok ( visual_sub , TRUE );
	wrefresh ( uif ) ;
	wrefresh ( visual ) ;
	wrefresh ( visual_sub ) ;
	
	while ( 1 ) {	
	    mvwgetstr ( uif , 2, 1, number ); 
		for ( p = number ; *p == ' ' || *p == '\t' ; ++p ) ;
		if ( *p == 'e' || *p == 'E' ) {
			mvwaddstr ( uif, 3, 1, "Bye Bye      ") ;
			wrefresh ( uif ) ; break ; 
		}
		switch ( *p ) {
			case '0' : case '1' : case '2' : case '3' : case '4' :
			case '5' : case '6' : case '7' : case '8' : case '9' :			
				val = atoi ( p ) ;
				if ( full() ) {
					mvwaddstr( uif, 3, 1, " Stack is full " );
					break ;
				}
				wscrl ( visual_sub  , 1 ) ;
				for ( i = 0 ; i < sp ; i++ )
					mvwprintw ( visual_sub, i, 0, "%d", stack [ i ] ) ;
				mvwprintw ( visual_sub , starty, startx,  "%d", val );
				(sp >= 7 ) ? starty = 8 : ++starty;
				stack [sp++] = val;
				mvwaddstr ( uif, 3, 1, "Done          " );
				break ;
			case 'p' : case 'P' :
				if ( empty()  ) {
					mvwaddstr ( uif, 3, 1, "No Data       " );
					break ;
				}
				mvwprintw ( visual_sub, --starty, 0, "%15s", "      " );
				mvwprintw ( uif, 3, 1, "%d            ", stack [--sp] ) ;
				break ;
			default :
				break ;
		}
		wmove ( uif, 2, 1 ) ;
		wclrtoeol ( uif ) ;
		wrefresh ( uif ) ;
		wrefresh ( visual ) ;
		wrefresh ( visual_sub ) ;
	} 
	endwin () ;	
}
