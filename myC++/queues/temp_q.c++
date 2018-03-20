# include <string.h>
# include <iostream>

using namespace std;
# include "queue.h"

int Queue :: enQ ( int item ) throw ( Queue :: Full ) {
	if ( full ( ) ) throw Queue :: Full ( );
	*write++ = item;
	if ( write >= end ) write = beg;
	nitems++;
	return 1;
}

int Queue :: deQ ( ) throw ( Queue :: Empty ){
	if ( empty ( ) ) throw Queue :: Empty( );
	int item;
	item = *read++;
	if ( read  >= end ) read = beg;
	nitems--;
	return item;
}

Queue & Queue :: operator = ( const Queue &q1 ) {
	if ( &q1 == this ) return *this;
	delete [] beg;
	nint = q1.nint;
	nitems = q1.nitems;
	beg = new int [nitems];
	end = beg + nitems;
	write = beg + ( q1.write - q1.beg );
	read = beg + ( q1.read - q1.beg );
	for ( int i = 0; i < nitems; i++ )
		beg[i] = q1.beg[i];
	return * this;
}

Queue & Queue :: operator += ( int num ) throw ( Full ) { 
	enQ ( num );
	return *this;	
}

int Queue :: operator -- ( ) throw ( Empty ) { 
	return deQ ( );
}

Queue & Queue :: operator += ( const Queue &q ) { 
	int tot_items, i;
	Queue temp_Q;

	tot_items = nitems + q.nitems;
	temp_Q.nitems = nitems;
	temp_Q.beg = new int [nitems];
	temp_Q.end = temp_Q.beg + nitems;
	temp_Q.write = temp_Q.beg + ( write - beg );
	temp_Q.read = temp_Q.beg + ( read - beg );
	for ( i = 0; i < nitems; i++ )
		temp_Q.beg[i] = beg[i] ;	
	delete [] beg;
	beg = new int[tot_items];
	end = beg + tot_items;
	nitems = tot_items;
	nint   = tot_items;
	write = beg + ( temp_Q.write - temp_Q.beg );
	read = beg + ( temp_Q.read - temp_Q.beg );
	for ( i= 0; i < temp_Q.nitems; i++ )
		beg[i] = temp_Q.beg[i];
	for ( int j = 0; i < tot_items ; i++, j++ )
		beg[i] = q.beg[j];
	return *this;
}

int Queue :: operator << ( int num ) throw ( Full ) { 
	enQ ( num );
	return 1;
}

int operator << ( int &num , Queue &q ) throw ( Queue :: Empty ) { 
	num = q.deQ ( );
	return num;
}

istream & operator >> ( istream &s, Queue &q ) throw ( Queue :: Full ) { 
	int num;

	while ( 1 ) {
		cout << "Enter a num to Enq ( -10 to stop ) : ";
		cin >> num;
		if ( num == -10 ) break;
		try {
			q.enQ ( num );
		}
		catch ( Queue :: Full a ) {
			throw  a;
		}
	}
	return s;
}

ostream & operator << ( ostream &s, Queue &q ) throw ( Queue :: Empty ) { 
	while ( 1 ) {
		try {
			s << q.deQ ( ) << " ";
		}
		catch ( Queue :: Empty a ) {
			throw a;
		}
	}
	return s;
}
