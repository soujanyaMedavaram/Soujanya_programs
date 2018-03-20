# include <stdio.h>
# include "../utils.h"

main ( ) {
	int semid, ret_val;
	semid = create_sem ( getuid () );
	printf ( " semid= %d: create sem\n", semid );
	ret_val =  sem_lock ( semid );
	if ( ret_val == 0 )
		printf ( " sem not locked\n" );
	else printf ( " sem locked \n" );
	close ( 1  ); close ( 2 ); close ( 0 );
	switch ( fork ( ) ) {
		case 0: while ( 1 );
		default : exit ( 0 );
	}
}

