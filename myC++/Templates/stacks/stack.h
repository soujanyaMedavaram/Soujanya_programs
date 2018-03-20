template <class T> class Stack {
	int nitems;
	int nint;
	T *beg;
	T *end;
	T *sp;

	public :
	int full ( ) const {
		return ( nitems ==  nint );
	}

	int empty ( ) const {
		return ( nitems == 0 );
	}

	class Full { };
	class Empty { };

	Stack ( int n = 50 ) {
		nitems = 0;
		nint = n;
		beg = new T[n];
		sp = beg;
		end = beg + n;
	}

	Stack ( const Stack & s1 ) {
		nint = s1.nint;
		nitems = s1.nitems;
		beg = new T[nint];
		end = beg + nint;
		sp = beg + ( s1.sp - s1.beg );
		for ( int i = 0; i < nint; i++ )
			beg[i] = s1.beg[i];
	}

	~Stack ( ) {
		delete [] beg;
	}
	
	int push ( T item ) throw ( Full );
	T pop ( ) throw ( Empty );
	Stack<T> & operator += ( T item ) throw ( Full );
	T operator-- ( ) throw ( Empty );
	T operator -- ( int num ) throw ( Empty );
	Stack<T> & operator += ( const Stack<T> &s );
	Stack<T> & operator = ( const Stack<T> &s );
	int operator << ( T item ) throw ( Full );
	friend T operator << ( T &num, Stack<T> &s ) throw ( Stack<T> :: Empty ){
		item = s.pop ( );
		return item;
	}

	friend istream & operator >> ( istream &is, Stack<T> &s ) 
							throw ( Stack<T> :: Full ){

		T item;
		cout << "Enter item to push\n";
		while ( cin >> item ) {
			try {
				s.push ( item );
			}
			catch ( Stack<T> :: Full a ) {
				throw a;
			}
			cout << "Enter item to push\n" ;
		}
		return is;
	}
	friend ostream & operator << ( ostream &os, Stack<T> &s )
							throw ( Stack<T> :: Empty ) {
		while ( 1 ) {
			try {
				os << s.pop ( ) << " ";
			}
			catch ( Stack<T> :: Empty a ) {
				throw a;
			}
		}
		return os;
	}
};

template <class T> int Stack <T> :: push ( T item ) throw ( Full ) {
	if ( full () )  throw Stack <T> :: Full ();
	*sp++ = item;
	nitems++;
	return 1;
}

template <class T> T Stack <T> :: pop ( ) throw ( Empty ) {
	if ( empty () )  throw Stack <T> :: Empty ();
	T item;
	sp--;
	item = *sp;
	nitems--;
	return item;
}

template <class T> Stack<T> & Stack<T> :: operator += ( T item ) throw ( Full )
{
	push ( item );
	return *this;
}

template <class T> T Stack<T> :: operator-- ( ) throw ( Empty ) {
	return pop ( );
}
template <class T> T Stack<T> :: operator-- ( int num ) throw ( Empty ) {
	return pop ( );
}
template <class T> Stack<T> & Stack<T> :: operator += ( const Stack<T> &s ) {
	int tot_items, i;
	Stack<T> temp_S;

	tot_items = nitems + s.nitems;
	temp_S.nitems = nitems;
	temp_S.beg = new T [ nitems ];
	temp_S.end = temp_S.beg + nitems;
	temp_S.sp = temp_S.beg + ( sp - beg );
	for ( i = 0; i < nitems; i++ )
		temp_S.beg[i] = beg[i];
	delete [] beg;
	beg = new T[tot_items];
	end = beg + tot_items;
	nitems = tot_items;
	nint = tot_items;
	sp = beg + ( temp_S.sp - temp_S.beg ) + (s.sp - s.beg );
	for ( i = 0; i < temp_S.nitems; i++ )
		beg[i] = temp_S.beg[i];
	for ( int j = 0; i < tot_items; i++, j++ )
		beg[i] = s.beg[j];
	return *this;
}
template <class T> Stack<T> & Stack<T> :: operator = ( const Stack<T> &s ) {
	if ( &s == this ) return *this;
	delete [] beg;
	nint = s.nint;
	nitems = s.nitems;
	beg = new T[nitems];
	end = beg + nitems;
	sp = beg + ( s.sp - s.beg);
	for ( int i = 0; i < nitems; i++ )
		beg[i] = s.beg[i];
	return * this;
}

template <class T> int Stack<T> :: operator << ( T item ) throw ( Full ) {
	push ( item );
	return 1;
}
