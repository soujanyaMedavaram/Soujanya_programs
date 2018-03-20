
# include <iostream>

using namespace std;
# include "stack.h"

int Stack :: push ( int item ) throw ( Stack :: Full ) {
	if ( full ( ) ) throw Stack :: Full ( );
	*sp++ = item;
	nitems++;
	return 1;
}

int Stack :: pop ( ) throw ( Stack :: Empty ){
	if ( empty ( ) ) throw Stack :: Empty( );
	int item;
	sp--;
	item = *sp;
	nitems--;
	return item;
}

Stack & Stack :: operator = ( const Stack &s1 ) {
	if ( &s1 == this ) return *this;
	delete [] beg;
	nint = s1.nint;
	nitems = s1.nitems;
	beg = new int [nitems];
	end = beg + nitems;
	sp  = beg + ( s1.sp - s1.beg );
	for ( int i = 0; i < nitems; i++ )
		beg[i] = s1.beg[i];
	return * this;
}

Stack & Stack :: operator += ( int num ) throw ( Full ) { 
	push ( num );
	return *this;	
}

int Stack :: operator -- ( ) throw ( Empty ) { 
	return pop ( );
}

int Stack :: operator -- ( int num ) throw ( Empty ) {
	return pop ( );
}

Stack & Stack :: operator += ( const Stack &s ) { 
	int tot_items, i;
	Stack temp_S;

	tot_items = nitems + s.nitems;
	temp_S.nitems = nitems;
	temp_S.beg = new int [nitems];
	temp_S.end = temp_S.beg + nitems;
	temp_S.sp = temp_S.beg + ( sp - beg );
	for ( i = 0; i < nitems; i++ )
		temp_S.beg[i] = beg[i] ;	
	delete [] beg;
	beg = new int[tot_items];
	end = beg + tot_items;
	nitems = tot_items;
	nint   = tot_items;
	sp = beg + ( temp_S.sp - temp_S.beg ) + ( s.sp - s.beg );
	for ( i= 0; i < temp_S.nitems; i++ )
		beg[i] = temp_S.beg[i];
	for ( int j = 0; i < tot_items ; i++, j++ )
		beg[i] = s.beg[j];
	return *this;
}

int Stack :: operator << ( int num ) throw ( Full ) { 
	push ( num );
	return 1;
}

int operator << ( int &num , Stack &s ) throw ( Stack :: Empty ) { 
	num = s.pop ( );
	return num;
}

istream & operator >> ( istream &is, Stack &s ) throw ( Stack :: Full ) { 
	int num;

	while ( 1 ) {
		cout << "Enter a num to Enq ( -10 to stop ) : ";
		is >> num;
		if ( num == -10 ) break;
		try {
			s.push ( num );
		}
		catch ( Stack :: Full a ) {
			throw  a;
		}
	}
	return is;
}

ostream & operator << ( ostream &os, Stack &s ) throw ( Stack :: Empty ) { 
	while ( 1 ) {
		try {
			os << s.pop ( ) << " ";
		}
		catch ( Stack :: Empty a ) {
			throw a;
		}
	}
	return os;
}
