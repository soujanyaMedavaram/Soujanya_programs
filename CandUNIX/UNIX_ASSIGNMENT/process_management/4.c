# include <stdio.h>
# include <unistd.h>

main ( ) {
	close ( 0 );
	close ( 1 );
	close ( 2 );
	setpgrp ( );
	while ( 1 );
}
