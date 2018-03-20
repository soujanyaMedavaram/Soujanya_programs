
# include <iostream>
using namespace std;
# include "stack.h"

main ( ) {
	Stack <char*> s1(5);
	int num;
	char* str;

	try {
		s1.push ( "hai10" );
		s1.push ( "hai20" );
		s1.push ( "hai30" );
		s1.push ( "hai40" );
		s1.push ( "hai50" );
		s1.push ( "hai60" );
	} catch (...) {
		cout << "Stack Overflow\n";
	}
	while ( !s1.empty ( ) ) {
		try {
			str = s1.pop ( );
			cout << "num deleted is " << str << endl;
		} catch (...) {
			cout << " Stack Underflow \n";
		}
	}
}
