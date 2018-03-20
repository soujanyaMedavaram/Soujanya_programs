
# include <iostream>
using namespace std;
# include "list.h"

main ( ) {
	List<int> s1;
	int num;
	char* str;

		cout << "hai\n";
		s1.push_back ( 10 );
		s1.push_back ( 20 );
		s1.push_back ( 30 );
		s1.push_back ( 40 );
		s1.push_back ( 50 );
		s1.push_back ( 60 );
	while ( 1 ) {
		try {
			num = s1.rem_beg ( );
			cout << "num deleted is " << num << endl;
		} catch (...) {
			cout << "List Empty \n";
			break;
		}
	}
	return 0;
}
