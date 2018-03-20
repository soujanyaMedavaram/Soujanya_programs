#include<curses.h>
#include<stdio.h>
main()

{
	char buff[9];
	int i,v;
	initscr();
	mvprintw(5,15,"enter ur string here :   ");
	refresh();
	for(i = 0; i < 4 ; i++)
	{
		noecho();
		v=getch();
		buff[i] = v;
		addch('*');
	}
	buff[i]='\0';
	system("clear");
//	if(!(strcmp(buff,"ganga")))
		printf("%s",buff);
/*	else
		printf("not a correct input");*/
	endwin();
}
	
