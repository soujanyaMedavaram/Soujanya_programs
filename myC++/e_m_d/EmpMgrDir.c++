//# include <iostream>
//using namespace std;

# include "derived_class.h"

main ( ) {
	Employee e1,e2;
	
	cin >> e1;// e1.getDetails ( );
	cin >> e2 ; //e2.getDetails ( );
	Manager m1, m2;
	cin >> m1; //m1.getDetails ( );
	cin >> m2; //m2.getDetails ( );
	m1 += e1; //m1.addEmp ( e1.getEmpId ( ) );
	m1 += e2; //m1.addEmp ( e2.getEmpId ( ) );
	cout << "\nMANAGER DETAILS\n";
	//m1.print ( );
	cout << m1;
	cout << "EMP GROUP LIST DETAILS\n";
	m1.printList ( );
	cout << "m1.rmvEmp ( e1.getEmpId ( ) )";
	m1 -= e1; //m1.rmvEmp ( e1.getEmpId ( ) );
	cout << " EMP GROUP LIST AFTER RMV EMP1\n";
	m1.printList ( );
/*	Director d1;
	d1.addMgr ( m1.getMgrId ( ) );
	d1.addMgr ( m2.getMgrId ( ) );*/

}



