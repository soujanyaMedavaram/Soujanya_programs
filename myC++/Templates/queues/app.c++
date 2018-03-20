
# include <iostream>
using namespace std;
# include "queue.h"

main ( ) {
	Queue <char*> s1(5);
	int num;
	char* str;

	try {
		s1.enQ  ( "hai10" );
		s1.enQ  ( "hai20" );
		s1.enQ  ( "hai30" );
		s1.enQ  ( "hai40" );
		s1.enQ  ( "hai50" );
		s1.enQ  ( "hai60" );
	} catch (...) {
		cout << "Queue Overflow\n";
	}
	while ( !s1.empty ( ) ) {
		try {
			str = s1.deQ ( );
			cout << "num deleted is " << str << endl;
		} catch (...) {
			cout << " Queue Underflow \n";
		}
	}
}
