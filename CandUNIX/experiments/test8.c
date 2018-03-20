# include <unistd.h>
# include <stdio.h>

main ( ) {
	if ( chdir ( "UNIX_ASSIGNMENT" ) < 0 )
		exit ( 1 );
	printf ( "chdir done : " );
	fflush ( stdout );
	system ( "pwd" );
}
