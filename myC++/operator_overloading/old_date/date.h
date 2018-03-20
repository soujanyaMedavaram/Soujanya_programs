// date.h
// All dates have to be post 01-01-1970

class date {
	int dd;
	int mm;
	int yy;

	void do_fragment ( char *date_str );

	public :
		struct bad { };
		date ( const char *str = "1/1/1970" ) { 
			char *d_str;
			d_str = str;
			do_fragment ( d_str );
		}
		int    operator-  ( const date &d1  ) throws bad;
		date   operator+  ( int ndays );
		date   operator-  ( int ndays );
		date & operaotr+= ( int ndays );
		date & operaotr-= ( int ndays );
		date & operator++ ( );
		date & operator-- ( );
		date & operator++ ( int dummy );
		date & operator-- ( int dummy );
		
		int operator>  ( const date &d2 );
		int operator<  ( const date &d2 ); 
		int operator>= ( const date &d1 ); 
		int operator<= ( const date &d1 ); 
		int operator== ( const date &d1 ); 
		int operator!= ( const date &d1 ); 


		friend ostream & operator<< ( ostream &s, const date &d1 );
		friend istream & operator>> ( istream &s, date &d1 );
};
