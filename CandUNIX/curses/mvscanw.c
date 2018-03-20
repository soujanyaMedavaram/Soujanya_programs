#include<curses.h>
#include<stdio.h>
main()

{
	char buff[9];
	int i,v;
	initscr();
	mvprintw(5,15,"enter ur string here :   ");
	refresh();
	system("clear");
	mvscanw(5,15,"%s ",buff);
	endwin();
}
	
