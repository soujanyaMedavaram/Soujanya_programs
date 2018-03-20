
# include <iostream>
using namespace std;
# include "queue.h"

main ( ) {
	Queue <int> s1(5);
	int num;

	try {
		s1.enQ  ( 10 );
		s1.enQ  ( 20 );
		s1.enQ  ( 30 );
		s1.enQ  ( 40 );
		s1.enQ  ( 50 );
		s1.enQ  ( 60);
	} catch (...) {
		cout << "Queue Overflow\n";
	}
	while ( !s1.empty ( ) ) {
		try {
			num = s1.deQ ( );
			cout << "num deleted is " << num << endl;
		} catch (...) {
			cout << " Queue Underflow \n";
		}
	}
}
