# include <menu.h>
# include <curses.h>

int get_request   ( WINDOW * );
int my_driver     ( MENU *, int c, int index );
void start_curses ( void );
void end_curses   ( void );
void erase_menu   ( MENU * );


char * option[] = {
	"First Item",
	"Second Item",
	"Third Item",
	"Exit",
	NULL
};

# define MAX_ITEM 20
static ITEM * items [ MAX_ITEM + 1 ];

main() {
	WINDOW *win1, *win2;
	MENU *m;
	ITEM **i;
	int rows, cols, k, c, done ;
	
	start_curses();
	done = FALSE;
	for ( k = 0; k < MAX_ITEM && option [k]; ++k )
		items [k] = new_item ( option [k], "");
	if ( !( m = new_menu ( items ) ) ) 
		error ( "Error return form new_menu ", NULL );
	scale_menu ( m, &rows, &cols );
	if ( win1 = newwin ( rows +2, cols +2, 0, 0 ) ) {
		set_menu_win ( m, win1 );
		set_menu_sub ( m, derwin ( win1, rows, cols, 1, 1 ) );
		box ( win1, 0, 0 );
		keypad ( win1, 1 );
	} else error ( "Error return from newwin", NULL );
	if ( post_menu ( m ) != E_OK )
		error ( "Error return from post_menu", NULL );
	else wrefresh ( win1 );
	win2 = menu_win ( m ) ; 

	while ( !done ) {
		switch ( menu_driver ( m, ( c = get_request ( win2 ) ) ) ) {
			case E_UNKNOWN_COMMAND :
					done = my_driver(m, c, item_index ( current_item (m)));
					break ;
			case E_REQUEST_DENIED :
				i = menu_items ( m );
				if ( c == REQ_NEXT_ITEM || c == KEY_DOWN )
					set_current_item ( m, i [ 0 ] ) ;
				else if ( c == REQ_PREV_ITEM || c == KEY_UP )
					set_current_item ( m, i [rows - 1] );
				else beep () ;
				break;
			default :
				break ;
		}
	}
	erase_menu ( m ) ;
	i = menu_items ( m );
	end_curses ( ) ;
	free_menu ( m ) ;
	while ( *i ) free_item ( *i++);
	exit ( 0 );
}

int get_request ( WINDOW * w ) {
	int c  = wgetch ( w ) ;

	switch ( c ) {
		case '\n'       :
		case '\r'       : return c; 
		case 0x10		: return REQ_PREV_ITEM; 
		case 0x0e 		: return REQ_NEXT_ITEM;
		case KEY_HOME	: return REQ_FIRST_ITEM; 
		case KEY_LL	 	: return REQ_LAST_ITEM; 
		case KEY_RIGHT 	: return REQ_RIGHT_ITEM;
		case KEY_LEFT 	: return REQ_LEFT_ITEM; 
		case KEY_UP		: return REQ_UP_ITEM;
		case KEY_DOWN	: return REQ_DOWN_ITEM; 
		case 0x15 		: return REQ_SCR_ULINE;
		case 0x04 		: return REQ_SCR_DLINE;
		case 0x06 		: return REQ_SCR_DPAGE; 
		case 0x02 		: return REQ_SCR_UPAGE; 
		case 0x18 		: return REQ_CLEAR_PATTERN; 
		case 0x08 		: return REQ_BACK_PATTERN;
		case 0x01 		: return REQ_NEXT_MATCH; 
		case 0x1a 		: return REQ_PREV_MATCH;
	}
}

int my_driver ( MENU *m, int key, int index ) {
	WINDOW * out_disp;
	out_disp = newwin ( 10, 40, 12, 5 );
	box ( out_disp, 0, 0 );
	wrefresh ( out_disp );
	if (key == '\n' || key == '\r' ) {
		switch ( index ) {
			case 0: waddstr ( out_disp, "First item is selected") ;break;
			case 1: waddstr ( out_disp, "Second item is selected") ;break;
			case 2: waddstr ( out_disp, "Third item is selected") ;break;
			case 3: waddstr ( out_disp, "Bye Bye!" ); wrefresh ( out_disp);
					return 1;
		}
		wrefresh ( out_disp );
	}
	return 0;
}

void start_curses ( void ) {
	initscr () ;
	nonl ();
	raw ();
	noecho ();
	wclear ( stdscr );
}
void erase_menu ( MENU * m ) {
	unpost_menu ( m ) ;
	WINDOW * w = menu_win ( m ) ;
	WINDOW * s = menu_sub ( m ) ;
	werase ( w );
	wrefresh ( w );
	delwin ( s ) ;
	delwin ( w ) ;
}
void end_curses ( void ) {
	refresh () ;
	endwin () ;
}

