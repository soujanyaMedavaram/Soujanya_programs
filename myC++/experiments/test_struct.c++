# include <iostream>
using namespace std;

struct hai1 {
		int a;
};
struct hai2 : public hai1 {
};

int main ( ) {
	struct hai2 h2;
	h2.a = 10;
	cout << h2.a;
	return 1;
}
