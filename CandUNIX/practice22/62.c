# include <stdio.h>

main ( ) {
	int x;
	if ( sizeof ( int ) > -1 )
		printf ( "Bangalore \n" );
	else printf ( "Bengaluru \n" );
	x = sizeof ( int );
	if ( x > -1 ) 
		printf ( "Bangalore this time\n" );
	else printf ( "Bengaluru again \n" );
}
