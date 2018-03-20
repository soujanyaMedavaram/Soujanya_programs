# include <stdio.h>
# include <stdlib.h>

main ( ) {
	printf ( "key = %d\n", atoi (getenv ("DBKEY") ) );
}
