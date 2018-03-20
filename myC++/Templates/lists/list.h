
template<class T> class List {
	struct Node {
		Node *prev;
		Node *next;
		T data;
	};

	Node *first;
	Node *last;
	int nitems;
	
	public :

	class Empty {
	};

	List ( ) {
		first = last = NULL;
		nitems = 0;
	}

	List<T> & push_front ( T data );
	List<T> & push_back ( T data );
	T rem_beg ( ) throw ( List<T> :: Empty );
	T rem_end ( ) throw ( List<T> :: Empty );

	List<T> & operator += ( T data ) {
		push_back ( data );
		return *this;
	}

	List<T> & operator -= ( T &data ) {
		rem_end ( data );
		return *this;
	}

	List<T> & operator += ( const List<T> &l ) {
		last->next = l.first;
		last = l.last;
		return *this;
	}

	List<T> & operator << ( T data ) {
		push_back ( data );
		return *this;
	}

	List<T> & operator >> ( T &data ) {
		data = rem_end ( );
		return *this;
	}

	friend void operator << ( T &data, List<T> &ll ) {
		data = ll.rem_beg ( );
	}
	friend void operator >> ( T data, List<T> &ll ) {
		ll.push_front ( data );
	}

	friend ostream & operator << ( ostream &os, const List<T> &list ) {
		Node *item;
		if ( list.nitems == 0 ) 
			throw List<T> :: Empty ( );
		else {
		for (item = list.first; item->next != NULL; 
									item = item->next ) 
			os << item->data;
		os  << item->data;
		}
		return os;
	}

	friend istream & operator >> ( istream &is, List<T> &list ) {
		T data;
		Node *item;
	
		cout << " Enter a element : ";
		while ( is >> data ) {
			item = new Node[sizeof(Node)];
			if ( list.nitems == 0 ) {
				list.first = item;
				item->prev = NULL;
			}
			else {
				item->prev = list.last;
				(list.last)->next = item;
			}
			item->next = NULL;
			item->data = data;
			list.last = item;
			list.nitems++;
		}
		return is;
	}
};

template<class T> List<T> & List<T> :: push_front ( T data ) {
	Node *item;
	item = new Node[sizeof(Node)];
	if ( nitems == 0 ) last = item;
	item->data = data;
	item->prev = NULL;
	nitems++;
	item->next = first;
	first->prev = item;
	first = item;
	return *this;
}

template<class T> List<T> & List<T> :: push_back ( T data ) {
	Node *item;

	item = new Node[sizeof(Node)];
	if ( nitems == 0 ) first = item;
	item->data = data;
	item->next = NULL;
	item->prev = last;
	if ( nitems > 0 )
	last->next = item;
	last  = item;
	nitems++;
	return *this;
}
template<class T> T List<T> :: rem_beg ( ) throw ( List<T> :: Empty ) {
	Node *item;
	T data;

	if ( nitems == 0 ) throw List<T>:: Empty ( );
	nitems--;
	item = first;
	first = first->next;
	data = item->data;
	delete [] item;
	return data;
}
template<class T> T List<T> :: rem_end ( ) throw ( List<T> :: Empty ) {
	Node *item;
	T data;	

	if ( nitems == 0 ) throw  List<T>:: Empty ( );
	nitems--;
	item = last;
	last = last->prev;
	last->next = NULL;
	data = item->data;
	delete [] item;
	return data;
}
