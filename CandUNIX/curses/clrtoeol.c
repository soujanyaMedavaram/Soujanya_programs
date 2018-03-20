#include<curses.h>
#include<stdio.h>
main()

{
	int i;
	initscr();
	for( i =2000;i--;addch('a'));
	move(22,10);
	addstr("any key to clear right half of the first 10 lines...");
	refresh();
	getch();
	for(i=0;i<10;i++)
	{
		move(i,40);
		clrtoeol();
	}
	refresh();
	getch();
	endwin();
}
	
