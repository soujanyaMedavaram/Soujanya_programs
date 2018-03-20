#include<stdio.h>
#include<curses.h>
main()
{
	int i =1 ;
	initscr();
	
	move(i +=2 ,10);
	
	attrset(A_BLINK);
	addstr("this is the BLINK -> ");
	
	standend();
	
	attron(A_BOLD);
	move(i +=2 ,10);
	addstr("this is the BOLD -> ");
	
	attroff(A_BOLD);
	attron(A_DIM);
	move(i +=2 ,10);
	addstr("this is the DIM-> ");


	attrset(A_BLINK | A_REVERSE | A_UNDERLINE);
	move(i +=2 ,10);
	addstr("this is the blink reverse underline-> ");
	
	attrset(0);	
	move(i +=2 ,10);
	addstr("this is the normal-> ");
	refresh();
	getch();
	endwin();
}
