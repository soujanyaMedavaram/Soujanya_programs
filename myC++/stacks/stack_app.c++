
# include <iostream>

using namespace std;

# include "stack.h"

main ( ) {
	Stack s1(5), s2, s, s3;
	string str;
	char *line, *p;
	int num;

	cin >> s2;
	//s2 += 50;
	//num = --s2;
	//cout << num << endl;
	//cin >> s1;
	//s2 += s1;
	s = s2;
	cout << s << endl;
	cout << s1 << endl;
exit ( 0 );

	line = new char[500];
	while ( 1 ) {
		cout << "num to push, D to pop, E to exit\n";
		cin >> str;
		line = ( char * )str.data ( ) ; 
		for ( p = line; p && isblank ( *p ); p++ );
		switch ( *p ) {
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				num = atoi ( p );
				try {
					s1.push ( num );
				}
				catch ( Stack::Full a ) { 
					cout << " Stack is full\n";
				}
				break;

			case 'd' : case 'D' :
				try {
					num = s1.pop ( );
					cout << num <<" deleted\n";
				}
				catch ( Stack::Empty a ) {
					cout << " Stack is empty\n";
				}
				break;

			case 'e' : case 'E' :
				try {
					while ( 1 )
						cout << --s1 << endl;
				}
				catch ( Stack::Empty a ) {
					cout << "Stack is empty\n" ;
				}
				exit ( 0 );
		}
	}
	delete [] line;
}
