# include <iostream>
# include <string.h>
# include <map>
# include <string>
# define MAX 50

using namespace std;

struct msstruct {
	long bsid;
	char msname[40];
};

int bsid[10] = { 10,20,30,40,50,60,70,80,90,100};
char msname[][10] = { "n1", "n2", "n3", "n4", "n5", "n6","n7", "n8",
								"n9","n10" };
char addr[][10] = { "1.2.3.4", "1.2.4.3","1.4.3.4","1.3.4.2","1.3.2.4",
			"1.4.2.3","4.1.2.3","4.2.1.3","4.3.2.1","3.1.2.4" };

typedef map<string, msstruct> IPMap;

class ip_map {
	msstruct ms[10];
	IPMap ip;
	char ip_addr[MAX]

	public:
		ip_map () { };
		~ip_map () { };
		
		void hash_init ( );
		void hashmap ( ) ;
		ostream & operator >> ( ostream &, ip_map & );
		ostream & operator << ( ostream &, ip_map & );
}

void ip_map :: hash_init ( ) {
	int i;
	for ( i = 0; i < 10; i++ ) {
		ms[i].bsid = bsid[i]; 
		strcpy (ms[i].msname,msname[i] ); 
	}
}

void ip_map :: hash_map ( ) {
	

int main ( ) {
	ip_map ob;
	string ip_addr;
	IPMap ip;
	int i;
	msstruct ms1;

	ob.hash_init ( );
	cin >> ip_addr;
	ob.hashmap ( );
}
int main( )  {
	string  ip_addr[40];
	msstruct ms[10], ms1;
	IPMap ip;
	int i;
	int bsid[10] = { 10,20,30,40,50,60,70,80,90,100};
	char msname[][10] = { "n1", "n2", "n3", "n4", "n5", "n6","n7", "n8",
								"n9","n10" };
	char addr[][10] = { "1.2.3.4", "1.2.4.3","1.4.3.4","1.3.4.2","1.3.2.4",
			"1.4.2.3","4.1.2.3","4.2.1.3","4.3.2.1","3.1.2.4" };
	for ( i = 0; i < 10; i++ ) {
		ms[i].bsid =bsid[i]; 
		strcpy ( ms[i].msname,msname[i] ); 
	}
	cout << "\n enter Ip address\n" ;
	for ( i = 0; i < 10; i++ ) {
		strcpy ( ip_addr , addr[i] );
		ip[ip_addr] = ms[i];
	}
	cout << "enter Ip addr for retrieving\n";
	cin >> ip_addr;
	ms1 = ip[ip_addr];
	cout << ms1.bsid << endl;
	cout << ms1.msname << endl;
	cout << " ALL contents\n";
	IPMap :: iterator p;
	for ( p = ip.begin(); p != ip.end(); p++ ) {
		cout << (*p).first << endl;
		cout << (*p).second.bsid << "  " << (*p).second.msname<<endl;
	}
}
