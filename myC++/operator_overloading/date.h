# ifndef _DATE_H
# define _DATE_H

// date.h
// All dates have to be post 01-01-1970

# include <string.h>
# include <iostream>
using namespace std;

struct bad_date { 
	int err_no;
	bad_date ( int n ) { err_no = n; }
};

class date {
	long days;

	struct ldate {
		int dd, mm, yy;
		ldate (int d, int m, int y) {
			dd = d; mm = m; yy = y;
		}
	};
	ldate  do_fragment ( const char * date_str ) throw (bad_date);
	void date_2_days ( const ldate & ) throw (bad_date);
	char * days_2_date ( ) throw ( bad_date );	
	public :
		date ( const char * str = NULL ) throw (bad_date) { 
			date_2_days ( do_fragment ( str ? str : "02/02/2002" ) );
		}
		date ( const int dd, const int mm, const int yyyy ) throw (bad_date) { 
			date_2_days ( ldate (dd, mm, yyyy) );
		}

		date & operator= ( const date &d ) {
			if ( &d == this ) return *this;
			days = d.days;
			return *this;
		}
		
		date ( const date &d ) {
			days = d.days;
		}
		operator char * ( )  const  throw ( bad_date ) ;

		int    operator-  ( const date &d1  ) {
			return (days - d1.days);
		}
		date   operator+  ( int ndays ) const {
			date d1;
			cout << "###########" << endl;
			cout << "days = " << days << endl;
			cout << "ndays = " << ndays << endl;
			cout << "days + ndays = " << days + ndays << endl;
			cout << "############" << endl;
			d1.days = days + (ndays+1);
			cout <<"##### d1.days = days + (ndays + 1 ) " << d1.days << endl;
			return d1;
		}
		date   operator-  ( int ndays ) const {
			date d1;
			d1.days = days - (ndays -1 );
			return d1;
		}
		date & operator+= ( int ndays ) {
			days += (ndays+1);
			return *this;
		}
		date & operator-= ( int ndays ) {
			days -= (ndays-1);
			return *this;
		}
		date & operator++ ( ) {
			days++;
			return *this;
		}
		date &  operator-- ( ) {
			days--;
			return *this;
		}
		date & operator++ ( int dummy ) {
			++days;
			return *this;
		}
		date &  operator-- ( int dummy ) {
			--days;
			return *this;
		}
		
		int operator>  ( const date &d ) const {
			if ( days > d.days )
				return 1;
			return 0;
		}
		int operator<  ( const date &d ) const{ 
			if ( days < d.days )
				return 1;
			return 0;
		}
		int operator>= ( const date &d ) const{ 
			if ( days >= d.days )
				return 1;
			return 0;
		}
		int operator<= ( const date &d ) const{ 
			if ( days <= d.days )
				return 1;
			return 0;
		}
		int operator== ( const date &d ) const{ 
			if ( days == d.days )
				return 1;
			return 0;
		}
		int operator!= ( const date &d ) const{ 
			if ( days != d.days )
				return 1;
			return 0;
		}
		friend ostream & operator<< ( ostream &s, const date &d1 ) 
		                   throw (bad_date) {
			s << (char *) d1;
			return s;
		}
		friend istream & operator>> ( istream &s, date &d1 ) 
						throw (bad_date) {
			string str;
			s >> str;
			d1.date_2_days ( d1.do_fragment ( str.data ( ) ) );	
			return s;
		}
};

# endif //_DATE_H
