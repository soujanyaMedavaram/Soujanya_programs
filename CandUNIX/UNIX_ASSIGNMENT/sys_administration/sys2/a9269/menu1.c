# include <menu.h>

char * colors [ 13 ] = { "Black ", "Charcoal " , "Light Gray ",
						 "Brown", "Camel", "Navy", "Light Blue", 
						 " Hunter Green", "Gold", "Burgundy",
						 "Rust ", "White", (char*) 0 
						};
ITEM *items [ 13 ] ;

main() {
	MENU *m ;
	ITEM ** i;
	char ** c;
	
	initscr () ;
	wclear (stdscr) ;

	for ( i = items, c = colors; *c; c++, i++ ) 
		*i = new_item ( *c, "" ) ;
	*i = 0 ;

	m = new_menu ( items ) ;
	post_menu ( m ) ;
	refresh ( ) ;
	sleep ( 5 ) ;
	unpost_menu ( m ) ;
	refresh ;
	free_menu ( m ) ;
	while ( *i )
		free_item ( *i++ ) ;
	endwin ();
}
