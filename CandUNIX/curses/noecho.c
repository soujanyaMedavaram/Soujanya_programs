#include<curses.h>
#include<stdio.h>

main()
{
	char buff[12];
	initscr();
	mvprintw(5,15,"enter ur string here");
	refresh();
	noecho();
	getstr(buff);
	clear();
	addstr(buff);
	refresh();
	endwin();
}
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
