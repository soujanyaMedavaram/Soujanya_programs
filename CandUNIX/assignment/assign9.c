# include <stdio.h>

main()
{
	int odd, leap, ord_odd;
	int month_odd, year_odd, leap_odd;
	int month_days, count;
	int year, month,year_dup;
	int i, x;
	enum {sunday = 0, monday, tuesday, wednesday,thursday, friday, saturday};
	printf ("\n enter the desired year and month\n");
	scanf( "%d%d", &year, &month);
	odd = month_odd =  leap_odd = ord_odd = leap = month_days = 0;
	count = 0;
	year_odd = 0;
	year_dup = year;
	while (year >= 100)
	{
		count++;
		if (count % 4 == 0)
			year_odd += 1;
		year_odd += 5;
		year = year - 100;
	}
	count = 0;
	year_odd = year_odd % 7;
	if (year >= 1)
		year--;
	leap = year / 4;
	ord_odd = year - leap;
	leap_odd = leap * 2;
	year_odd += ord_odd + leap_odd;
	year_odd = year_odd % 7;
	year = year_dup;

	/* calculating month odd days*/
	for ( i = 1; i < month; i++)
	{
		if ( i <= 7)
		{
			if((i % 2) != 0)
				month_odd += 31;
			else
				month_odd += 30;
		}
		else if ( i > 7)
		{
			if((i % 2) != 0)
				month_odd += 30;
			else
				month_odd +=31;
		}
	}
	if(month > 2)
	{
		month_odd -= 30;
		if (year % 4 == 0)
			month_odd += 29;
		else 
			month_odd +=28;
	}
	month_odd++;
	month_odd = month_odd % 7;
	
	// calculating total odd days

	odd = year_odd + month_odd;
	odd = odd % 7;
	

	/* calculating days in the given month*/

	if (month == 2)
	{
		if (year % 4 == 0)
			month_days = 29;
		else
			month_days = 28;
	}
	else 
	{
		if (month > 7)
		{
			if (month % 2 == 0)
				month_days = 31;
			else 
				month_days = 30;
		}
		else if (month <= 7)
		{
			if (month % 2== 0)
				month_days = 30;
			else 
				month_days = 31;
		}
	}
	/* printing calender*/
	count = odd;	
	odd++;
	printf ("\n********************************************************\n");
	printf ("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	for ( i = 1; i < odd; i++)
		printf( "\t");
	for ( i = 1; i <= month_days; i++)
	{
		printf("%d\t",i);
		count++;
		if (count % 7 == 0)
			printf("\n");
	}
	
	printf("\n************************************************************\n");
}





