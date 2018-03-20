# include <stdio.h>
# include "../utils.h"

main ( ) {
	int semid, ret_val;
	semid = open_sem ( getuid ( ) );
	printf ( " semid= %d: open sem\n", semid );
	ret_val = sem_lock ( semid );
	if ( ret_val == 0 )
		printf ( " sem not locked\n" );
	else printf ( " sem locked \n" );
	sem_unlock ( semid );
	rem_sem ( semid );
	exit ( 0 );
}


