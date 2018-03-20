
# ifndef _STACK_H
# define _STACK_H

class Stack {
	int nitems;
	int nint;
	int *beg;
	int *sp;
	int *end;

	public :
	int full ( ) const {
		return ( nitems == nint );
	}

	int empty ( ) const {
		return ( nitems == 0 );
	}

	class Full { };
	class Empty { };

	Stack ( int n = 50 ) {
		nitems = 0;
		nint = n;
		beg = new int[n] ;
		sp = beg;
		end = beg + n;
	}

	Stack ( const Stack & s1 ) {
		nint = s1.nint;
		nitems = s1.nitems;
		beg = new int [nint];
		end = beg + nint;
		sp = beg + ( s1.sp - s1.beg );
		for ( int i = 0; i < nint; i++ )
			beg[i] = s1.beg[i];
	}

	~Stack ( ) {
		delete [] beg;
	}


	int push ( int item ) throw ( Full );
	int pop ( ) throw ( Empty ) ; 
	Stack & operator += ( int num ) throw ( Full );
	int operator -- ( ) throw ( Empty );
	int operator -- ( int num ) throw ( Empty );
	Stack & operator += ( const Stack &s );
	Stack & operator = ( const Stack &s1 );
	int operator << ( int num ) throw ( Full ); 
	friend int operator << ( int &num , Stack &s ) throw ( Stack :: Empty ) ;
	friend istream & operator >> ( istream &s, Stack &s ) 
						   throw ( Stack :: Full ); 
	friend ostream & operator << ( ostream &s, Stack &s ) 
				           throw ( Stack :: Empty ) ;
};

# endif //_STACK_H
