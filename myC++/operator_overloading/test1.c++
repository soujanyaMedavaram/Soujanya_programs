# include <iostream>
using namespace std;

main ( ) {
	int dd, mm, yyyy, bal_days;
	int month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int ord_year, leap_year,i ,day_mon = 0, day_year, tot_days;
	int year, mon, days;
	cout << " enter dd mm yyyy\n";
	cin>>dd;
	cin>>mm;
	cin>>yyyy;
	leap_year = yyyy / 4;
	ord_year = yyyy - leap_year;
	day_year = ord_year * 365 + leap_year * 366;
	if ( yyyy % 4 == 0 )
		month[2] = 29;
	for ( i = 1; i < mm; i++ )
		day_mon += month[i];
	tot_days = day_year + day_mon + dd;
	cout << "tot _ days = "<< tot_days<< endl;
	//tot_days += 1095;
	tot_days += 1;
	cout << "tot_days+30 = " << tot_days;
	year = 0; mon = 0; days = 0;
	while ( tot_days >= 365 ) {
		year++;
		if ( year % 4 ) tot_days -= 365;
		else tot_days -= 366;
	}
	if ( year % 4 == 0 ) month[2] = 29;
	for ( i = 1; tot_days >month[2] ; i++ )
		tot_days -= month[i];
	mon = i;
	if ( tot_days <= 0 ) days = 1;
	else days = tot_days;
	cout << "year = "<< year << endl;
	cout << "month = " << mon << endl;
	cout << "days = " << days << endl;
}

