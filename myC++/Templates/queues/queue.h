template <class T> class Queue {
	int nint;
	int nitems;
	T *beg;
	T *end;
	T *write;
	T *read;

	public :
	int full ( ) const {
		return ( nitems ==  nint );
	}

	int empty ( ) const {
		return ( nitems == 0 );
	}

	class Full { };
	class Empty { };

	Queue ( int n = 50 ) {
		beg = new T[n] ;
		write = beg;
		read = beg;
		end = beg + n;
		nitems = 0;
		nint = n;
	}

	Queue ( const Queue & q1 ) {
		nint = q1.nint;
		nitems = q1.nitems;
		beg = new T [nint];
		end = beg + nint;
		write = beg + ( q1.write - q1.beg );
		read = beg + ( q1.read - q1.beg );
		for ( int i = 0; i < nint; i++ )
			beg[i] = q1.beg[i];
	}

	~Queue ( ) {
	}
	
	int enQ ( T item ) throw ( Full );
	T deQ ( ) throw ( Empty );
	Queue<T> & operator += ( T item ) throw ( Full );
	T operator-- ( ) throw ( Empty );
	T operator -- ( int num ) throw ( Empty );
	Queue<T> & operator += ( const Queue<T> &s );
	Queue<T> & operator = ( const Queue<T> &s );
	int operator << ( T item ) throw ( Full );
	friend T operator << ( T &item, Queue<T> &q ) throw ( Queue<T> :: Empty ){
		item = q.deQ ( );
		return item;
	}

	friend istream & operator >> ( istream &is, Queue<T> &q ) 
							throw ( Queue<T> :: Full ){
		T item;

		cout << "Enter item  : ";
		while ( cin >> item ) {
			try {
				q.enQ ( num );
			}
			catch ( Queue<T> :: Full a ) {
				throw  a;
			}
			cout << "Enter item : ";
		}
		return s;
	}
	

	friend ostream & operator << ( ostream &os, Queue<T> &s )
							throw ( Queue<T> :: Empty ) {
							
		while ( 1 ) {
			try {
				s << q.deQ ( ) << " ";
			}
			catch ( Queue<T> :: Empty a ) {
				throw a;
			}
		}
		return s;
	}
};

template <class T> int Queue <T> :: enQ ( T item ) throw ( Full ) {
	if ( full ( ) ) throw Queue :: Full ( );
	*write++ = item;
	if ( write >= end ) write = beg;
	nitems++;
	return 1;
}

template <class T> T Queue <T> :: deQ ( ) throw ( Empty ) {
	if ( empty ( ) ) throw Queue :: Empty( );
	T item;
	item = *read++;
	if ( read  >= end ) read = beg;
	nitems--;
	return item;
}

template <class T> Queue<T> & Queue<T> :: operator += ( T item ) throw ( Full )
{
	enQ ( item );
	return *this;	
}

template <class T> T Queue<T> :: operator-- ( ) throw ( Empty ) {
	return deQ ( );
}
template <class T> T Queue<T> :: operator-- ( int num ) throw ( Empty ) {
	return deQ ( );
}
template <class T> Queue<T> & Queue<T> :: operator += ( const Queue<T> &q ) {
	int tot_items, i;
	Queue<T> temp_Q;

	tot_items = nitems + q.nitems;
	temp_Q.nitems = nitems;
	temp_Q.beg = new T[nitems];
	temp_Q.end = temp_Q.beg + nitems;
	temp_Q.write = temp_Q.beg + ( write - beg );
	temp_Q.read = temp_Q.beg + ( read - beg );
	for ( i = 0; i < nitems; i++ )
		temp_Q.beg[i] = beg[i] ;	
	delete [] beg;
	beg = new T[tot_items];
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
template <class T> Queue<T> & Queue<T> :: operator = ( const Queue<T> &q1 ) {
	if ( &q1 == this ) return *this;
	delete [] beg;
	nint = q1.nint;
	nitems = q1.nitems;
	beg = new T [nitems];
	end = beg + nitems;
	write = beg + ( q1.write - q1.beg );
	read = beg + ( q1.read - q1.beg );
	for ( int i = 0; i < nitems; i++ )
		beg[i] = q1.beg[i];
	return * this;
}

template <class T> int Queue<T> :: operator << ( T item ) throw ( Full ) {
	enQ ( item );
	return 1;
}
