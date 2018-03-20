# include <stdio.h>
main ( ) {
struct abc {
int a;
};
struct abc a = {10}; 
struct abc b = {20}; 
if ( a == b ) 
	printf ( "hai\n" );
else 
	printf  ( "not workinf\n" );
}

