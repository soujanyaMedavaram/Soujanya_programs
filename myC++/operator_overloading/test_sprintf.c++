# include <iostream>

using namespace std;

main ( ) {
	char *str;
	double x = 1234.5678;
	sprintf ( str, "%lf", x );
	printf ( "%s->str\n", str );
}
