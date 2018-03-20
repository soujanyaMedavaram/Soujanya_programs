
# include <iostream>
using namespace std;
# include "list.h"

main ( ) {
	List<char*> s1;
	int num;
	char* str;

		cout << "hai\n";
		s1.push_back ( "hai10" );
		s1.push_back ( "hai20" );
		s1.push_back ( "hai30" );
		s1.push_back ( "hai40" );
		s1.push_back ( "hai50" );
		s1.push_back ( "hai60" );
	while ( 1 ) {
		try {
			str = s1.rem_beg ( );
			cout << "num deleted is " << str << endl;
		} catch (...) {
			cout << "List Empty \n";
			break;
		}
	}
	return 0;
}
