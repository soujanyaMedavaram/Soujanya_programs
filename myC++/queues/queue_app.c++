# include <iostream>

using namespace std;

# include "queue.h"

main ( ) {
	Queue q1(5), q2, q, q3;
	string str;
	char *line, *p;
	int num;

	//q2 += 50; 	//Enq
//	num = --q;	//Deq
//	q2 += q1;
//	cin >> q3;
//	cout << q3;
//	cin >> q1;
//	num = --q1;
//	cout << num << endl;
//	cout << q1;
//	cin >> q1;
//	cin >> q2;
//	q1 += q2;
//	cout << q1;

	line = new char[500];
	while ( 1 ) {
		cout << "num to enq, D to deque, E to exit\n";
		cin >> str;
		line = ( char * )str.data ( ) ; 
		for ( p = line; p && isblank ( *p ); p++ );
		switch ( *p ) {
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				num = atoi ( p );
				try {
					q1.enQ ( num );
				}
				catch ( Queue::Full a ) { 
					cout << " Queue is full\n";
				}
				break;

			case 'd' : case 'D' :
				try {
					num = q1.deQ ( );
					cout << num <<" deleted\n";
				}
				catch ( Queue::Empty a ) {
					cout << " Queue is empty\n";
				}
				break;

			case 'e' : case 'E' :
				try {
					while ( 1 )
						cout << --q1 << endl;
				}
				catch ( Queue::Empty a ) {
					cout << "Queue is empty\n" ;
				}
				exit ( 0 );
		}
	}
	delete [] line;
}
