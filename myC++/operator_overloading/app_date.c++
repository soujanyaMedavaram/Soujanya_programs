# include <iostream>

using namespace std;
# include "date.h"

int main ( ) {

	try {
		date d1, d2( "02.03.1999" ), d3,d4;
		char ch;
		int ndays;
	
		cout << "\n enter a date\n";
		cin >> d1;
		cout << d1<< endl;
		d4 = d1;
		cout << "date++ is " << d1++ << endl;
		d1 = d4;
		cout << "++date is " << ++d1 << endl;
		d1 =d4;
		cout << "date-- is " << d1-- << endl;
		d1 = d4;
		cout << "--date is " << --d1 << endl;
		d1 = d4;
		cout << "1.suntract date\n 2. add ndays \n 3.subtract ndays\n"
							"4.compare two dates\n";
		cout << "Enter ur choice\n";
		cin >> ch;
		switch ( ch ) {
			case '1': 
				cout << "enter any date\n";
				cin >> d4;
				ndays = d1 - d4;
				cout << "ndays = d1 - d4 " << ndays;
				break;
			case '2':
				cout << "\n enter days\n";
				cin >> ndays;
				d4 = d1 + ndays;
				cout << " d4 = d1 + ndays "<< d4 << endl;
				d1 += ndays;
				cout << " d1 += ndays is "<< d1 << endl;
				d1 = d3;
				break;
			case '3':
				cout << "\n enter days\n";
				cin >> ndays;
				d4 = d1 - ndays;
				cout << " d4 = d1 - ndays "<< d4 << endl;
				d1 -= ndays;
				cout << " d1 -= ndays is "<< d1 << endl;
				break;
			case '4' :
					cout << "enter date\n";
				cin >> d4;
				if ( d1 > d4 )
					cout << " d1 > d2 " << endl;
				else cout << "d1 not > d2 " << endl;
				if ( d1 < d4 ) 
					cout << "d1 < d4 " << endl;
				else cout << " d1 not < d4 " << endl;
				if ( d1 >= d4 )
					cout << "d1 >= d4 " << endl;
				else 
					cout << "d1 not >= d4" << endl;
				if ( d1 <= d4 )
					cout << "d1 <= d4" << endl;
				else
					cout << "d1 not <= d4" << endl;
				if ( d1 == d4 )
					cout << "d1 == d4\n";
				else 
					cout << "d1 not == d4\n";
				if ( d1 != d4 )
					cout << "d1 != d4\n";
				else
					cout << "d1 not != d4\n";
				break;
		}
	}
	catch ( bad_date b ) {
		cout << " Error in date manipulation.Err_no: " << b.err_no << endl;
		exit ( b.err_no );
	}

}
			

			

				

