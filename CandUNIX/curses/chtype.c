#include<stdio.h>
#include<curses.h>
main()
{
	chtype ch;
	initscr();
	cbreak();
	mvprintw(5,22,"enter the character : ");
	refresh();
	ch = getch();
	move(22,25);
	printw("the character entered by u is %c\n",ch);
	refresh();
	getch();
	endwin();
}
