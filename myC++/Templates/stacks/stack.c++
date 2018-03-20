# include "stack.h"

template <class T> int Stack <T> :: push ( T item ) throw ( Stack <T> :: Full ) {
	if ( full () )  throw Stack <T> :: Full ();
	*sp++ = item;
	nitems++;
	return 1;
}

template <class T> T Stack <T> :: pop ( ) throw ( Stack <T> :: Empty ) {
	if ( empty () )  throw Stack <T> :: Empty ();
	T item;
	sp--;
	item = *sp;
	nitems--;
	return item;
}

template class Stack <int>;
