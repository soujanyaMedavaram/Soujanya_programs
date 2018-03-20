# include <stdio.h>
int day_fo_year(int, int, int);

	static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};
main ()
{
	int year, month, day;
	int day_year;
	printf ("\n enter the year \n month\n day\n");
	scanf("%d%d%d",&year, &month, &day);
	day_year = day_of_year(year, month,day);
	printf ("day of the year is %d \n",day_year);
}

int day_of_year(int year, int month ,int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for ( i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}
