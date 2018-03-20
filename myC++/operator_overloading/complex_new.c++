# include <iostream>
using namespace std;
# include "complex_new.h"


int main  (  ) {
	complex c1, c2(20), c3(20.3,12.3), c4;

	cout << "Enter real and imaginary parts\n";
	cin >> c1;
	cin >> c2;
	c4 = c1;
	cout << "COMPARISION\n" ;
	if ( c1 == c2 )
		cout << "EQUAL\n";
	else cout << "UNEQUAL\n";
	cout << "ADDITION\n" ;
	c3 = c1 + c2;
	cout << c3 << endl;
	c1 += c2;
	cout << c1 << endl;
	c1 = c4;
	cout << "DIFFERENCE\n" ;
	c3 = c1 - c2;
	cout << c3 << endl;
	c1 -= c2;
	cout << c1 << endl;
	c1 = c4;
	cout << "MULTIPLICATION\n";
	c3 = c1 * c2;
	cout << c3 << endl;
	c1 *= c2;
	cout << c1 << endl;
	c1 = c4;
	cout << "DIVISION\n" ;
	c3 = c1 / c2 ;
	cout << c3 << endl;
	c1 /= c2;
	cout << c1 << endl;
	c1 = c4;
	cout << "MISCELLENEOUS\n";
	c3 = c1 + 10;
	cout << "c3 = c1 + 10 is "<< c3 << endl;
	c3 = 10 + c1;
	cout << "c3 = 10 + c1 is "<< c3 << endl;
	return 0;
}
