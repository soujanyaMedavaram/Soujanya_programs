# include <stdio.h>

main (  ) {
	printf ( " parent\n" );
	if ( fork(  ) == 0 ) {
		printf ( " child\n" );
	}
	wait ( 0 );
}
