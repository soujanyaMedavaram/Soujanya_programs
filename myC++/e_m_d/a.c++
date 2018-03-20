# include <iostream>
using namespace std;
# include <list>

class A {
	int x;
	public:
		A(int a = 0) { x = a; }
		static list<A *> lst;
};
list<A *> A::lst;

int main() {
	A * a;
	a = new A (123);
	A::lst.push_front (a);
}
