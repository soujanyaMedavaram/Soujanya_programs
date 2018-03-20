# ifndef _QUEUE_H
# define _QUEUE_H

class Queue {
	int nint;
	int nitems;
	int *beg;
	int *end;
	int *write;
	int *read;

	public :
	int full ( ) const {
		return ( nitems == nint );
	}

	int empty ( ) const {
		return ( nitems == 0 );
	}

	class Full { };
	class Empty { };

	Queue ( int n = 50 ) {
		beg = new int[n] ;
		write = beg;
		read = beg;
		end = beg + n;
		nitems = 0;
		nint = n;
	}

	Queue ( const Queue & q1 ) {
		nint = q1.nint;
		nitems = q1.nitems;
		beg = new int [nint];
		end = beg + nint;
		write = beg + ( q1.write - q1.beg );
		read = beg + ( q1.read - q1.beg );
		for ( int i = 0; i < nint; i++ )
			beg[i] = q1.beg[i];
	}

	~Queue ( ) {
		delete [] beg;
	}


	int enQ ( int item ) throw ( Full );
	int deQ ( ) throw ( Empty ) ; 
	Queue & operator += ( int num ) throw ( Full );
	int operator -- ( ) throw ( Empty );
	Queue & operator += ( const Queue &q );
	Queue & operator = ( const Queue &q1 );
	int operator << ( int num ) throw ( Full ); 
	friend int operator << ( int &num , Queue &q ) throw ( Queue :: Empty ) ;
	friend istream & operator >> ( istream &s, Queue &q ) 
						   throw ( Queue :: Full ); 
	friend ostream & operator << ( ostream &s, Queue &q ) 
				           throw ( Queue :: Empty ) ;
};

# endif //_QUEUE_H
