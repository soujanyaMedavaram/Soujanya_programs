# include <stdio.h>
# include "../../sb.h"

main ( ) {
	int semid;
	semid = sem_lock ( getuid( ), "lock" );
	system ( "ipcs" );
	sleep ( 5 );
	printf ( "\n locked semma phore\n" );
	sem_lock ( semid, "unlock" );
	printf ( "success\n" );
}
