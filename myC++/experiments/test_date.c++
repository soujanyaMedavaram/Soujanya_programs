# include <iostream>
# include "../operator_overloading/date.h"

using namespace std;

class hai {
	date d1;
	date d2;
	public :
		void get_date ( ) {
			cin >> d1;
			cin >> d2;
		}

		void put_date ( ) {
			cout << d1;
			cout << d2;
		}
};

int  main ( ) {
		hai h1;
		h1.get_date ( );
		h1.put_date ( );

}
