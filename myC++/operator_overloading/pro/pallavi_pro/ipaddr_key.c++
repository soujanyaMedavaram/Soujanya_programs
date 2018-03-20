# include <iostream>
# include <string.h>
# include <map>
# include <string>

using namespace std;

struct msstruct {
	long bsid;
	char msname[40];
};

typedef map<string, msstruct> IPMap;

int main( )  {
	string ip_addr;
	msstruct ms;
	IPMap ip;

	ms.bsid = 1234;
	strcpy ( ms.msname, "ms_name" );
	cout << "\n enter Ip address\n" ;
	cin >> ip_addr;
	ip[ip_addr] = ms;
	cout << "enter Ip addr for retreving\n";
	cin>> ip_addr;
	ms = ip[ip_addr];
	cout << ms.bsid << endl;
	cout << ms.msname << endl;
}
