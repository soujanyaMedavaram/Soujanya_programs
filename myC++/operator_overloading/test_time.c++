# include <iostream>
# include <time.h>

using namespace std;

main ( ) {
	time_t time_time;
	time_time = time ( NULL );
	cout << ctime ( &time_time );
	cout << "hai" << "\\";
}
