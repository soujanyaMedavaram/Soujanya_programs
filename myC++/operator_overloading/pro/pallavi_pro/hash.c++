# include <iostream>
# include <string>
# include <vector>

using namespace std;

# define IP_SIZE	4

struct msstruct {
	long bsid;
	char msname[40];
	msstruct ( long sid = 0, const char * name = "" ) {
		bsid = sid;
		strcpy ( msname, name );
	}
};

struct ip_addr {
	unsigned char addr [IP_SIZE];
	ip_addr ( const char * adr ) {
		for ( int i = 0; i < IP_SIZE; i++ ) {
			addr[i] = atoi ( adr );
			while ( isdigit (*adr) ) adr++;
			if ( *adr == '.' ) adr++;
		}
	}
};

int hash_function ( const ip_addr * );

class cache {
		msstruct  * db;
		int nitems;
	public:
		cache ( int n ) : db ( new msstruct [n] ) { nitems = n; }
		msstruct &  operator[] ( const ip_addr &  ip ) {
			return db [ hash_function ( & ip ) % nitems ];
		}
};

int hash_function ( const ip_addr * ip ) {
	int res;

	res = 0;
	for ( int i = 0; i < IP_SIZE; i++ )
		res += ip->addr[i];
	cout << ip << "  ==>  " << res << endl;
	return res;
}

void print ( const ip_addr &  x );

cache ms ( 100 );

int main ( ) {
	ip_addr  a ("89.0.0.210");
	ip_addr  b ("89.0.0.220");
	ip_addr  c ("89.0.0.230");
	msstruct msa ( 123, "pallavi" );
	msstruct msb ( 456, "shastry" );
	msstruct msc ( 789, "soujanya" );
	msstruct &  y = ms[a];
	ms [a] = msa;
	ms [b] = msb;
	ms [c] = msc;
	print ( a );
	print ( b );
	print ( c );
}

void print ( const ip_addr &  x ) {
	msstruct &  y = ms[x];
	cout << y.bsid << " " << y.msname << endl;
}
