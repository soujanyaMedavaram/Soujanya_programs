class Node {
	public :
	Node *prev;
	Node *next;
	int data;
};

class List {
	Node *beg;
	Node *end;
	Node *node;
	Node *curr;
	int nitems;
	
	public :
	class Empty {
	};
	List ( ) {
		beg = end = node = curr = NULL;
		nitems = 0;
	}

	List & ins_beg ( int num );
	List & ins_end ( int num );
	int rem_beg ( ) throw ( List :: Empty );
	int rem_end ( ) throw ( List :: Empty );

	List & operator += ( int num );
	List & operator -= ( int &num );
	List & operator + ( int num );
	List & operator - ( int num );
	friend List & operator + ( int num, List &ll );
	friend List & operator - ( int num, List &ll );
	int operator << ( int num );
	int operator >> ( int &num );
	friend int operator << ( int &num, List &ll );
	friend int operator >> ( int num, List &ll );
	friend ostream & operator << ( ostream &os, List &list );
	friend istream & operator >> ( istream &is, List &list );
};
