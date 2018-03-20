# include <curses.h>
main()
{
	chtype ch;
	int x, y;
	x = y = 0;
	initscr();
	noecho();
	cbreak();
	move(y, x);
	refresh();
	while (1)
	{
		ch = getch();
		switch(ch)
		{
			case 'U':
				y--;
				break;

			case 'D':
				y++;
				break;

			case 'R':
				x++;
				break;

			case 'L':
				x--;
				break;
	
			case 8:
				x--;
				break;

			case 27:
				out();
				break;

			case 10:
				y++;
				break;
				
			default:
				addch(ch);
				refresh();
				x++;
				break;
		}
		if(y < 0){ printf("error"); y=0;}
		if(y > 23){ printf("error"); y=23;}
		if(x < 0){ printf("error"); x=0;}
		if(x > 79){ printf("error"); y=79;}
		move(y,x);
		refresh();
	}
}


out()
{
	endwin();
	exit(0);
}
