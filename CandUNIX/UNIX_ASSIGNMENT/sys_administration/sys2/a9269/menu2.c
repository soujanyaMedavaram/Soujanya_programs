# include <menu.h>
# include <curses.h>


char *option [] = { "Current date",
					"Current time",
					"User-details",
					"List of files",
					"Exit",
					NULL
				};

main () {
	MENU *m;
	ITEM *items [ 10 ] ;
	ITEM ** i ;
	char ** c ;
	int rows, cols;
	WINDOW *w ;

	initscr () ;
	wclear ( stdscr ) ;
	while ( *c )
		*i++ = new_item (*c++, "" );
	*i = NULL ;
	m = new_menu ( i = items );
//	scale_menu ( m, &rows, &cols ) ;
//	w = newwin ( rows + 2 , cols + 2  , 0, 0 );
//	set_menu_win ( m, w );
	post_menu (m);
	refresh () ;
//	box ( w, 0, 0 ) ;
//	wrefresh ( w ) ;
	int x = getch () ;
	while (*i){
			if (! strcmp ( item_name ( *i) ,"Current date"  ) ) 
				system ( "date  +%D");
			else if (! strcmp ( item_name ( *i) ,"Current time"  ) ) 
				system ( "date +%T");
			else if (! strcmp ( item_name ( *i) ,"List of files "  ) ) 
				system ( "ls -l");
			else if ( ! strcmp ( item_name ( *i) , "Exit" ) ) 
				exit ( 0 ) ;
			set_item_value ( *i, FALSE ) ;
			refresh () ;
		} ++i ;
	}
	unpost_menu(m);
	refresh () ;
	free_menu ( m ) ;
	for ( i = items; *i ; ++i);
		free_item ( *i ) ;
	endwin () ;
}
