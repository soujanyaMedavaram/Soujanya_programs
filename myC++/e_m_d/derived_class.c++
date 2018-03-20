// # include <iostream>
// using namespace std;

# include "derived_class.h"

list<Employee *> Employee::emp;
list<Manager *> Manager :: mgr;
list<Director *> Director :: dir;

Employee & Employee :: operator = ( const Employee &e ) {
	strcpy ( first_name, e.first_name );
	strcpy ( family_name, e.family_name );
	strcpy ( middle_name, e.middle_name );
	strcpy ( addr, e.addr );
	strcpy ( Org_name, e.Org_name );
	strcpy ( qual , e.qual );
	DOJ  = e.DOJ ;
	DOB  = e.DOB ;
	emp_id = e.emp_id;
	desg   = e.desg;
	sal    = e.sal;
	department = e.department;
	return *this;
}

void Employee :: printList ( ) {
	list<Employee *> :: iterator p;
	for ( p = Employee::emp.begin(); p != Employee::emp.end(); p++ ) 
		(*p)->print ( );
}

void Employee :: print ( ) {
	cout << first_name << ' ' << middle_name << ' ' << family_name << endl;
	cout << "addr is " << addr;
	cout << "  " << Org_name << endl;
	cout << "Qualification : " << qual << endl;
	cout << " DOJ     DOB " << endl; 
	cout << DOJ << ' ' ;
	cout << DOB << endl;
	cout << "Emp_id Mgr_id Dir_id\n " ;
	cout << emp_id << endl;
	cout << "Desg : " << desg << " " << "sal : " << sal << endl;
	cout << "Department : " << department << endl;
}

int  Employee :: getEmpId ( ) {
	return emp_id;
}


int Employee :: getDetails ( ) {
	cout << "Enter first_name middle_name family_name " << endl;
	cin >> first_name >> middle_name >> family_name;
	cout << "Enter Addr , Org_name, Qualification\n";
	cin >> addr >> Org_name >> qual;
	cout << "Enter DOJ DOB\n";
	try {
		cin >> DOJ ;
		cin >> DOB;
	} catch (...) {
		cout << "Bad date\n";
	}
	cout << "Enter emp_id,  designation, sal, dept\n";
	cin >> emp_id >> desg >> sal >> department;
	return 1;
}

Manager & Manager :: operator = ( const Manager &m ) {
	Employee :: operator = ( m );
	level = m.level;
	Mgr_id = m.Mgr_id;
	return *this;
}

int Manager :: getDetails ( ) {
	Employee :: getDetails ( );
	cout << "Enter level , Mgr_id" ;
	cin >> level ;
	cin >> Mgr_id;
	return 1;
}

int Manager :: getMgrId ( ) {
	return Mgr_id;
}

void Manager :: print ( ) {
	Employee :: print ( );
	cout << "level : " << level;
	cout << "\nMgr_id : " << Mgr_id << endl;
}

void Manager :: printList ( ) {
	list<Employee*>:: iterator p;
	for ( p = Manager:: emp_group.begin(); p != Manager :: emp_group.end( ); 
												++p )
		(*p)->print ( );
}

int Manager :: addEmp ( int Emp_id ) throw ( Manager :: No_emp ) {
	list<Employee*>::iterator p;
	int empid;
	for ( p = Employee :: emp.begin ( ); p != Employee :: emp.end ( ) ;p++ ) {
		empid = ( *p )-> Employee :: getEmpId ( );
		if ( empid == Emp_id ) { 
			Manager :: emp_group.push_back ( *p );
			return 1;
		}
	}
	throw Manager :: No_emp ( );
}

int Manager :: rmvEmp ( int Emp_id ) throw ( Manager :: No_emp ) {
	list<Employee*>::iterator p;
	int empid;
	for ( p = Employee :: emp.begin ( ); p != Employee :: emp.end ( ) ;p++ ) {
		empid = ( *p )-> getEmpId ( );
		if ( empid == Emp_id ) { 
			Manager :: emp_group.remove( *p );
			return 1;
		}
	}
	throw Manager :: No_emp ( );
}

int Manager :: changeDetails ( int Emp_id ) {
}

Director & Director :: operator = ( const Director &d ) {
	Dir_id = d.Dir_id;
	Manager :: operator = ( d );
}

int Director :: getDetails ( ) {
	Manager :: getDetails ( );
	cout << "Enter Dir_id : ";
	cin >> Dir_id;
	return 1;
}

void Director :: print ( ) { 
	Manager :: print ( );
	cout << "Dir_id : " << Dir_id << endl;
}

int Director :: addMgr( int Mgr_id ) throw ( Director :: No_mgr ) {
	list<Manager*>::iterator p;
	int mgrid;
	for ( p = Manager :: mgr.begin ( ); p != Manager :: mgr.end ( ) ;p++ ) {
		mgrid = ( *p )-> Manager :: getMgrId ( );
		if ( mgrid == Mgr_id ) { 
			Director :: mgr_group.push_back ( *p );
			return 1;
		}
	}
	throw Director :: No_mgr ( );
}
/*int Manager :: addEmp ( int Emp_id ) throw ( Manager :: No_emp ) {
	list<Employee*>::iterator p;
	int empid;
	for ( p = Employee :: emp.begin ( ); p != Employee :: emp.end ( ) ;p++ ) {
		empid = ( *p )-> Employee :: getEmpId ( );
		if ( empid == Emp_id ) { 
			Manager :: emp_group.push_back ( *p );
			return 1;
		}
	}
	throw Manager :: No_emp ( );
}*/

int Director :: rmvMgr( int Mgr_id ) throw ( Director :: No_mgr ) {
	list<Manager*>::iterator p;
	int mgrid;
	for ( p = Manager :: mgr.begin ( ); p != Manager :: mgr.end ( ) ;p++ ) {
		mgrid = ( *p )-> Manager :: getMgrId ( );
		if ( mgrid == Mgr_id ) { 
			Director :: mgr_group.remove ( *p );
			return 1;
		}
	}
	throw Director :: No_mgr ( );
}

void Director :: printList ( ) {
	list<Manager*>:: iterator p;
	for ( p = Director :: mgr_group.begin(); p != Director :: mgr_group.end( ); 
												++p )
		(*p)->print ( );
}

istream & operator >> ( istream &is, Employee &e1 ) {
	e1.getDetails ( );
	return is;
}

ostream & operator << ( ostream &os, Employee &e1 ) {
	e1.print ( );
	return os;
}

istream & operator >> ( istream &is, Manager &m1 ) {
	m1.getDetails ( );
	return is;
}

ostream & operator << ( ostream &os, Manager &m1 ) {
	m1.print ( );
	return os;
}

istream & operator >> ( istream &is, Director &d1 ) {
	d1.getDetails ( );
	return is;
}

ostream & operator << ( ostream &os, Director &d1 ) {
	d1.print ( );
	return os;
}

Manager & Manager :: operator += ( Employee &e1 ) throw ( Manager :: No_emp ) {
	try {
		addEmp ( e1.Employee :: getEmpId ( ) );
	}catch ( Manager :: No_emp a ) {
		throw a;
	}
	return *this;
}

Manager & Manager :: operator -= ( Employee &e1 ) throw ( Manager :: No_emp ) {
	try {
		rmvEmp ( e1.Employee :: getEmpId ( ) );
	} catch (Manager :: No_emp a ) {
		throw a;
	}
	return *this;
}
