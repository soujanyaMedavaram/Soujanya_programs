#include<curses.h>
#include<stdio.h>
main()

{
	int i;
	initscr();
	for( i =2000;i--;addch('a'));
	move(10,25);
	addstr("any key to clear right half of the first 10 lines...");
	move(10,40);
	refresh();
	getch();
	clrtobot();
	refresh();
	getch();
	endwin();
}
	
