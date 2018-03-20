# include <stdio.h>
# include <sys/sem.h>
# include <sys/ipc.h>
# include <sys/types.h>
//# include "../../sb.h"

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

 sem_lock ( int pid , char *status ) {
	struct sembuf sops[2]; 
	union semun un_sem;
	int semid;
	un_sem.val = 0;

	sops[1].sem_num = 0;
	sops[1].sem_op = 1;
	sops[1].sem_flg = 0; 
	if ( !strcmp ( status, "lock" ) ) {
		sops[0].sem_num = 0;
		sops[0].sem_op = 0;
		sops[0].sem_flg = 0;
		if ( (semid = semget ( pid , 1, 0600 | IPC_CREAT  )) < 0 )
			if ( ( semid = semget ( pid, 0, 0600 | IPC_CREAT ) )< 0 )
				do_exit ( 1 , "semaphore creation failed\n" );
		if ( semctl ( semid, 0, SETVAL , un_sem) < 0 )
			do_exit ( 2, "semaphore failed at semctl\n" );
		if ( semop ( semid , sops, 2 ) < 0 )
			do_exit ( 3, " 1 semop failed\n" );
		return semid;
	}
	else if ( !strcmp ( status, "unlock" ) ) {
		sops[0].sem_num = 0;
		sops[0].sem_op = -1;
		sops[0].sem_flg = 0;
		if ( semop ( pid, sops, 1 ) < 0 )
			do_exit ( 4, " 2 semop failed\n" );
		return;
	}
}
