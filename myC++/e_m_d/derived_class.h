# include <list>
# include <iostream>
using namespace std;

# include "../operator_overloading/date.h"

class Employee {
	char first_name[20];
	char family_name[20];
	char middle_name[20];
	char addr[35];
	char Org_name[15];
	char qual[15];
	date DOJ;
	date DOB;
	int emp_id;
	int desg;
	int sal;
	short department;


	public :
		static list<Employee *> emp;
		Employee ( ) {
			emp.push_back(this);
		}
		~Employee ( ) { }
		Employee & operator = ( const Employee &e );
		virtual void printList ( ); 
		virtual void print ( ) ;
		int getEmpId ( );
		int getMgrId ( );
		int getDirId ( );
		virtual int getDetails ( );
		friend ostream & operator << ( ostream &os, Employee &e1 );
		friend istream & operator >> ( istream &is, Employee &e1 );
};

class Manager : public Employee {
	int Mgr_id;
	short level;

	public :
		class No_emp { };
		list<Employee*> emp_group;
		static list<Manager*> mgr;
		Manager ( ) { mgr.push_back ( this ); }
		~Manager ( ) { }
		Manager & operator = ( const Manager & );
		int getDetails ( );
		int getMgrId ( );
		void print ( ) ;
		void printList ( );
		int addEmp ( int Emp_id ) throw ( No_emp );
		int rmvEmp ( int Emp_id ) throw ( No_emp );
		Manager & operator += ( Employee & ) throw ( Manager :: No_emp );
		Manager & operator -= ( Employee & ) throw ( Manager :: No_emp );
		int changeDetails ( int Emp_id );
		friend ostream & operator << ( ostream &os, Manager & );
		friend istream & operator >> ( istream &is, Manager & );
};

class Director : public Manager {
	int Dir_id;

	public :
		class No_mgr { };
		list<Manager*> mgr_group;
		static list<Director*> dir;
		Director ( ){ dir.push_back ( this ); }
		~Director ( ){ }
		Director & operator = ( const Director & );
		int getDetails ( );
		int addMgr ( int Emp_id ) throw ( No_mgr );
		int rmvMgr ( int Emp_id ) throw ( No_mgr );
		void print ( );
		void printList ( );
		friend ostream & operator << ( ostream &os, Director & );
		friend istream & operator >> ( istream &is, Director & );
};
