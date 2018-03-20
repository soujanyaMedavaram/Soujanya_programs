# include <curses.h>
main(){
	initscr();
	waddch (stdscr,ACS_HLINE);
	waddch (stdscr,ACS_VLINE);
	waddch (stdscr,ACS_DARROW);
	waddch (stdscr,ACS_UARROW);
	wrefresh(stdscr);
	endwin();
}
