#include <iostream>

using namespace std;


# include "list.h"

List & List :: ins_beg ( int num ) {
	Node *item;
	item = new Node[sizeof(Node)];
	if ( nitems == 0 ) end = item;
	item->data = num;
	item->prev = NULL;
	nitems++;
	item->next = beg;
	beg->prev = item;
	beg = item;
	return *this;
}

List & List :: ins_end ( int num ) {
	Node *item;
	item = new Node[sizeof(Node)];
	if ( nitems == 0 ) beg = item;
	item->data = num;
	item->next = NULL;
	item->prev = end;
	end->next = item;
	end  = item;
	return *this;
}

int List :: rem_beg ( ) throw ( List :: Empty ) {
	Node *item;
	int num;

	if ( nitems == 0 ) throw List:: Empty ( );
	nitems--;
	item = beg;
	beg = beg->next;
	num = item->data;
	delete [] item;
	return num;
}

int List :: rem_end ( ) throw ( List :: Empty ) {
	Node *item;
	int num;
	
	if ( nitems == 0 ) throw  List :: Empty ( );
	nitems--;
	item = end;
	end = end->prev;
	end->next = NULL;
	num = item->data;
	delete [] item;
	return num;
}
List & List :: operator += ( int num ) {
	ins_end ( num );
	return *this;
}
List & List :: operator -= ( int &num ) {
	num = rem_end ( );
	return *this;
}
List & List :: operator + ( int num ) {
	ins_end ( num );
	return *this;
}
List & List :: operator - ( int num ) {
	rem_end ( );
	return *this;
}
List & operator + ( int num, List &ll ) {
	ll.ins_beg ( num );
	return ll;
}
List & operator - ( int num, List &ll ) {
	ll.rem_beg ( );
	return ll;
}
int List :: operator << ( int num ) {
	ins_end ( num );
	return 1;
}
int List :: operator >> ( int &num ) {
	num = rem_end ( );
	return num;
}
int operator << ( int &num, List &ll ) {
	num = ll.rem_beg ( );
	return num;	
}
int operator >> ( int num, List &ll ) {
	ll.ins_beg ( num );
	return 1;
}
istream & operator >> ( istream &is, List &list ) {
	int num;
	Node *item;

	while ( 1  ) {
		cout << " Enter a element :(-10 to stop ) ";
		is >> num;
		if ( num == -10 ) break;
		item = new Node[sizeof(Node)];
		if ( list.nitems == 0 ) {
			list.beg = item;
			cout << "2\n";
			item->prev = NULL;
		}
		else {
			item->prev = list.end;
			(list.end)->next = item;
		}
		item->next = NULL;
		item->data = num;
		list.end = item;
		list.nitems++;
	}
	return is;

}

ostream & operator << ( ostream &os, List &list ) {
	Node *item;
	if ( list.nitems == 0 ) 
		cout << " No elements\n";
	else {
	for (item = list.beg; item->next != NULL; 
								item = item->next ) 
		os << item->data;
	os  << item->data;
	}
	return os;
}
