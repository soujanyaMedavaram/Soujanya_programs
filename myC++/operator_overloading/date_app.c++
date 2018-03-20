# include <iostream>

using namespace std;

# include "date.h"

main ( ) {
	date d1, d2( "02/03/2009" ), d3;
	cin >> d1;
	d3 = d1;
	cout << d1 << endl;
	int x = d1 - d2;
	cout << x << endl;
	d3 = d1 + 10;
	cout << d3 << endl;
	d1 += 10;
	cout << d1 << endl;
	d1 = d3;
	d1 -= 10;
	cout << d1 << endl;
	d1 = d3;
	cout

}
