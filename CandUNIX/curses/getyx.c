#include<curses.h>
main()
{
	char  jyothi[31] ;
	int x,y;
	
	initscr();
	move(2,16);
	addstr("enter the string:");
	refresh();
	
	getyx(stdscr,y,x);
	sprintf(jyothi,"row %d col %d",x,y);
	
	move(3,17);

	addstr(jyothi);
	refresh();

	getch();

	endwin();
}	
