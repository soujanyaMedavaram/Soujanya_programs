# include <stdio.h>
# include <sys/sem.h>
# include <sys/ipc.h>
# include <sys/types.h>
//# include "../../sb.h"


sem_lock ( int cmd ) {
	int semid;
	struct sembuf sops[1]; 

	if ( (semid = semget ( getuid() , 1, 0600 )) < 0 ) 
		do_exit ( 2, "database not yet started up\n" );

	if ( cmd == 0 ) {
		sops[0].sem_num = 0;
		sops[0].sem_op = -1;
		sops[0].sem_flg = 0;
		if ( semop ( semid , sops, 1 ) < 0 )
			do_exit ( 3, " 1 semop failed\n" );
		return semid;
	}
	else if ( cmd == 1 ) {
		sops[0].sem_num = 0;
		sops[0].sem_op = 1;
		sops[0].sem_flg = 0;
		if ( semop ( semid, sops, 1 ) < 0 )
			do_exit ( 4, " 2 semop failed\n" );
		return;
	}
}
