
class huge {
	char sign;			// One way of representing huge
	char *integral;
	char *decimal;

	// private member functions ( Not part of the interface )

	huge  add ( const huge &b ) const;
	huge  sub ( const huge &b ) const;
	int compare ( const huge &b ) const; // returns 01a>b ,
	void do_fragment ( const char *);

	// Implementation of the interface depends upon the representation

	public :
		huge ( double  a = 0 ) { 
			char *str;
			if ( a != 0 ) {
				str = new char[20];
				sprintf ( str, "%lf", a );
			}
			else str = strdup ( "\0" );
			do_fragment ( str );
			delete [] str;
		}

		huge ( const char * );

		// 3 members below not needed for shallow objects
		~huge ( ) {
			delete [] integral;
			delete [] decimal ;
		}

		huge ( const huge &b ) {					// For call by value
			sign = b.sign;
			integral = strdup ( b.integral );
			decimal  = strdup ( b.decimal  );
		}
			
		huge & operator= ( const huge &b ) 	{			// For return by value
			if ( & b == this ) return *this;
			cout << "hai in op=\n";
			sign = b.sign;
			cout << "ONE\n";
			integral = strdup ( b.integral );
			cout << "TWO\n";
			decimal  = strdup ( b.decimal  );
			cout << "THREE\n";
			return *this;
		} 


		// cast operator(s)

		operator char * ( ) { 
			char *p ;
			p = new char[strlen ( integral ) + strlen ( decimal ) + 2];
			if ( sign == '-' )
				 strcpy ( p, "-" );
			else strcpy ( p, "+" ); 
			strcat ( p, integral );
			strcat ( p, "." );
			strcat ( p, decimal  );
			cout << "in char* " << p << endl;
			return p;
		}

		// Arithmetic operators

		huge & operator+= ( const huge &b );
		huge & operator-= ( const huge &b );
		huge & operator*= ( const huge &b );
		huge & operator/= ( const huge &b );

		friend huge operator+ ( const huge &a, const huge &b );
		friend huge operator- ( const huge &a, const huge &b );
		friend huge operator* ( const huge &a, const huge &b );
		friend huge operator/ ( const huge &a, const huge &b );
		friend int operator== ( const huge &a, const huge &b );
		friend int operator!= ( const huge &a, const huge &b );
		friend int operator>  ( const huge &a, const huge &b );
		friend int operator<  ( const huge &a, const huge &b );
		friend int operator>= ( const huge &a, const huge &b );
		friend int operator<= ( const huge &a, const huge &b );
		friend istream & operator>>  ( istream &s, huge &a );
		friend ostream & operator<<  ( ostream &s, const huge &a );
};
