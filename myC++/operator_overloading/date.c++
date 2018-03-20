# include <iostream>
using namespace std;

# include "date.h"

const int month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void date :: date_2_days ( const ldate &d1 ) throw (bad_date) {
	int leap_years, ord_years, i, leap;

	if ( d1.yy <= 0 || d1.mm > 12 || d1.mm < 1 || d1.dd < 1 )
		throw bad_date ( 1 );
	if ( d1.yy % 4 == 0 && d1.mm == 2 ) leap = 1;
	else leap = 0;
	if ( d1.dd > month[d1.mm] + leap )
		throw bad_date ( 2 );
	leap_years = d1.yy / 4;
	ord_years  = d1.yy - leap_years;
	days = ord_years * 365 + leap_years * 366;
	if ( d1.yy >= 1752 ) days -= 21;
	for ( i = 1; i < d1.mm ; i++ )
		days += month[i];
	days += d1.dd+1;
}

date :: ldate  date :: do_fragment ( const char * date_str )
		throw (bad_date) {
	int dd, mm, yy;

	while ( isblank ( *date_str ) ) date_str++;
	if ( !isdigit (*date_str) ) throw bad_date(1);
	dd = atoi ( date_str );
	while ( isdigit (*date_str) ) date_str++;
	if ( !*date_str ) throw bad_date(2);
	mm = atoi ( ++date_str );
	while ( isdigit (*date_str) ) date_str++;
	if ( !*date_str ) throw bad_date(3);
	yy = atoi ( ++date_str );
	return ldate (dd, mm, yy);
}

date :: operator char * ( )  const  throw ( bad_date ) {
	static char p[11];
	int year, mon, d_days, tot_days, leap, ll, i;
	
	year = mon = d_days = 0;
	tot_days = days;
	if ( tot_days < 365 ) throw bad_date  ( 3 );
	while ( tot_days >= 365 ) {
		year++;
		if ( year == 1752 ) tot_days -= ( 365 -19 );
		else if ( year % 4 ) tot_days -= 365;
		else tot_days -= 366;
	}
	if ( year % 4 == 0 ) leap = 1;
	else leap = 0;
	if ( year == 1752 ) tot_days += 21;
	for ( i = 1; ; i++ ) {
		if ( i == 2 ) ll = leap;
		else ll = 0;
		if ( tot_days < month[i] + ll ) break;
		tot_days -= month[i] + ll;
	}
	mon = i;
	if ( tot_days <= 0 ) d_days = 1;
	else d_days = tot_days;
	sprintf ( p, "%d/%d/%d", d_days, mon, year );
	return p;
}
