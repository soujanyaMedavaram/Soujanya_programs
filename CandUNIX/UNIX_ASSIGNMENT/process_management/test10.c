# include <stdio.h>
# include <unistd.h>

main ( ) {
	system ( "pwd" );
	chdir ( "." );
	system ( "pwd" );
}
