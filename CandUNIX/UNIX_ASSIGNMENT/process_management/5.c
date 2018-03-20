# include <stdio.h>

main ( ) {
	
	printf ( "%d->pid\n", getpid ( ) );
	switch ( fork ( ) ) {
		case -1: fprintf ( stderr, "fork failed \n" );
				 break;

		case 0:	system ( "ls -l > temp" );
				system ( "wc < temp" );
				system ( "ls -l | wc" );
				printf ( "%d->pid in child\n", getpid ( ) );
				break;
		}
	exit ( 0 );
}
