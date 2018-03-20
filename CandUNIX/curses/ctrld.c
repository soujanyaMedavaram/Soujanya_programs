# include <curses.h>
main()
{
	char *word = "UTTARA";
	char *word1 = "DAKSHINA";
	initscr();
	while (1)
	{
		printw ("%s\n", word);
		printw ("%s\n", word1);
		refresh();
		getch();
	}
	endwin();
}
