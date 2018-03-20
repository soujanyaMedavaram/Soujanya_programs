# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

main ( int argc, char *argv[] ) {
	*++argv;
	switch ( fork ( ) ) {
		case 0:
			execvp ( *argv, argv );
	}
	printf ( "<%s>\n", *argv );
	wait ( 0 );
	exit ( 0 );
}
