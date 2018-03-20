# include <iostream>
# include <string.h>
# include <time.h>

using namespace std;

# include "date.h"

void do_fragment ( char *date_str ) {
	int month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for ( ; isbalnk ( *date_str ); date_str++ );
	for ( int i = 0, int coutn = 0; date_str ; date_str++ ) {
		if ( *date_str == '//' ) {
			count++;
			word[i] = '\0';
			i = 0;
			if ( count == 1 ) {
				d1.dd = atoi ( word );
			else if ( count == 2 )
				d1.mm = atoi ( word );
			continue;
		}
		word[i++] = *date_str;
	}
	if ( count == 3 && i > 0) 
		d1.yyyy = atoi ( word );
	else {
		cerr << "Wrong fromat of date\n";
		exit ( 1  );
	}
	if ( d1.yyyy % 4 ) 
		month[2] = 29;
	for ( i = 1; i <= 12; i++ ) 
		if ( d1.mm == i ) 
			if ( d1.dd > month[i] ) {
				cerr << "Wrong days in given date\n";
				exit ( 2 );
			} else break;
	if ( i > 12 ) {
		cerr << "Wrong month in given date\n" ;
		exit ( 3 );
	}
}

int date :: operator- ( date &d1 ) throws date::bad {
	struct tm st_time;
	time_t time1_sec, time2_sec;
	
	st_time.tm_mday = dd;
	st_time.tm_mon  = mm;
	st_time.year    = yyyy;
	time1_sec = mktime ( &tm );
	if ( time1_sec == -1 )
		throw date :: bad();
	st_time.tm_mday = d1.dd;
	st_time.tm_mon  = d1.mm;
	st_time.year    = d1.yyyy;
	time2_sec = mktime ( &tm );
	if ( time2_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	return (time1_sec - time2_sec);
}

date  date :: operator+ ( int ndays ) {
	struct tm *st_time;
	time_t time1_sec;
	date d1;

	st_time->tm_mday = dd;
	st_time->tm_mon  = mm;
	st_time->year    = yyyy;
	time1_sec = mktime ( tm );
	time1_sec += (ndays * 24 * 60 * 60 );
	if ( time1_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	st_time = gmtime ( &time1_sec );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	d1.dd   = st_time->tm_mday;
	d1.mm   = st_time->tm_mon;
	d1.yyyy = st_time->tm_year;

	return d1;
}

date  date :: operator- ( int ndays ) {
	struct tm *st_time;
	time_t time1_sec;
	date d1;

	st_time = new  tm[sizeof(st_time)];
	st_time->tm_mday = dd;
	st_time->tm_mon  = mm;
	st_time->year    = yyyy;
	time1_sec = mktime ( tm );
	time1_sec -= (ndays * 24 * 60 * 60 );
	if ( time1_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	st_time = gmtime ( &time1_sec );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	d1.dd   = st_time->tm_mday;
	d1.mm   = st_time->tm_mon;
	d1.yyyy = st_time->tm_year;
	return d1;
}

date & date :: operator+= ( int ndays ) {
	struct tm *st_time;
	time_t time1_sec;

	st_time = new  tm[sizeof(st_time)];
	st_time->tm_mday = dd;
	st_time->tm_mon  = mm;
	st_time->year    = yyyy;
	time1_sec = mktime ( tm );
	time1_sec += (ndays * 24 * 60 * 60 );
	if ( time1_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	st_time = gmtime ( &time1_sec );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	dd   = st_time->tm_mday;
	mm   = st_time->tm_mon;
	yyyy = st_time->tm_year;
	return *this;
}

date & date :: operator-= ( int ndays ) {
	struct tm *st_time;
	time_t time1_sec;

	st_time = new  tm[sizeof(st_time)];
	st_time->tm_mday = dd;
	st_time->tm_mon  = mm;
	st_time->year    = yyyy;
	time1_sec = mktime ( tm );
	time1_sec -= (ndays * 24 * 60 * 60 );
	if ( time1_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	st_time = gmtime ( &time1_sec );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	dd   = st_time->tm_mday;
	mm   = st_time->tm_mon;
	yyyy = st_time->tm_year;
	return *this;
}

date operator+ ( int ndays, const date &d1 ) {
	struct tm *st_time;
	time_t time1_sec;
	date d2;

	st_time->tm_mday = d1.dd;
	st_time->tm_mon  = d1.mm;
	st_time->year    = d1.yyyy;
	time1_sec = mktime ( tm );
	time1_sec += (ndays * 24 * 60 * 60 );
	if ( time1_sec == -1 ) {
		cerr << "The date should be from 1/1/1970\n";
		exit ( 1 );
	}
	st_time = gmtime ( &time1_sec );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	d2.dd   = st_time->tm_mday;
	d2.mm   = st_time->tm_mon;
	d2.yyyy = st_time->tm_year;

	return d2;
}

int operator> ( const date &d1, const dte &d2 ) {
	struct tm st_time;
	time_t  time1_sec, time2_sec;

	st_time.tm_mday = d1.dd;
	st_time.tm_mon  = d1.mm;
	st_time.tm_year = d1.year;
	time1_sec = mktime ( &st_time );
	if ( st_time == NULL ) {
		cerr << "The operation on date cross limit(1/1/1970)\n";
		exit ( 2 );
	}
	st_time.tm_mday = d2.dd;

}
istream & operator>> ( istream &s, date &d1 ) {
	string d_str;
	char *date_str;

	cin >> d_str;
	date_str = strdup ( d_str.data( ) );
	d1.do_fragment ( date_str );
	return s;
}

ostream &operator<< ( ostream &s, date &d1 ) {
	cout << d1.dd << "\\" << d1.mm << "\\" << d1.yyyy << endl;
}

main ( ) {
	date d1("02/03/1999"), d2, d3;
	int days, ch;
	cout << "Enter a date\n";
	cin >> d1;
	cout << "1.subtract  DATE \n2.subtract days\n3.add days\n" ;
	cin >>ch;
	switch ( ch ) {
		case 1:
			cout << "Enter date\n";
			cin >> d2;
			days = d1 - d2;
			cout << days;
			break;
		case 2:
			cout << "Enter days\n";
			cin >> days;
			d3 = d1 - days;
			d3 = days - d1;
			d1 =- days;
			cout << d3;
			cout << d1;
			cout << endl;
			break;
		case 3:
			cout << "Enter days\n";
			cin >> days;
			d3 = d1 + days;
			d3 = days + d1;
			d1 += days;
			cout << d3;
			cout << d1;
			cout << endl;
			break;
	}
}


