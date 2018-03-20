# include <iostream>

using namespace std;

class A {
	int a;
	public :
		virtual void fun ( ) {
			cout << "In a\n";
		}
};
class B : public A {
	public :
		void fun ( ) {
			cout << "In b\n";
		}
};
class C : public B {
	public :
		void fun ( ) {
			cout << "In c\n" ;
		}
};


int main ( ) {
	A *pa,a;
	B *pb,b;
	C *pc,c;
	pc = &a;
	pc->fun ( );
	pc = &b;
	pc->fun ( );
	pc = &c;
	pc->fun ( );
}
