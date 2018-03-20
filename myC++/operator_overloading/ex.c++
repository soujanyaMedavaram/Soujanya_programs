# include <iostream>

using namespace std;
class hai {
public:
struct bad {
	int x;
	bad(int a) { x = a; }
};
};

int sub ( void ) throw () ;
int sub1( void ) throw (hai :: bad) ;

int main ( ) throw () {
	cout << "Start\n";
	for ( int i = 0; i < 2; i++ ) {
		try {
			if (i) sub ( );
			else sub1 ( );
		}
		catch ( hai :: bad b ) {
			cout << "We caught " << b.x << endl;
		}
	}
	cout << "End\n";
}

int sub ( ) throw ( ) {
	throw hai :: bad (10);
}

int sub1 ( ) throw (hai :: bad) {
	throw hai :: bad (22);
}
