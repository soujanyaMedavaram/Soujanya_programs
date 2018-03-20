# include <stdio.h>
# include "../../sb.h"
# include <sys/sem.h>
# include <sys/ipc.h>
# include <fcntl.h>
# include <sys/types.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main () {
	int fd;
	char c = 'b';
	int i, j;
	struct sembuf sops[2]; 
	int semid;
	union semun un_sem;

	un_sem.val = 0;

	sops[0].sem_num = 0;
	sops[0].sem_op = 0;
	sops[0].sem_flg = 0;
	sops[1].sem_num = 0;
	sops[1].sem_op = 1;
	sops[1].sem_flg = 0;
	if ( (semid = semget ( getuid ( ), 1, 0600 | IPC_CREAT  )) < 0 )
//		if ( ( semid = semget ( getuid ( ), 0, 0600 | IPC_CREAT ) )< 0 )
			do_exit ( 1 , "semaphore creatin failed\n" );
//	if ( semctl ( semid, 0, SETVAL , un_sem) < 0 )
//		do_exit ( 2, "semaphore failed at semctl\n" );

	fd = open ( "test", O_CREAT | O_APPEND | O_RDWR , 0660 );

	if ( semop ( semid , sops, 2 ) < 0 )
		do_exit ( 3, "semop failed\n" );
	for ( i = 0; i < 100; i++ ) {
		write ( fd, &c, 1 );
		for ( j = 0; j < 10000000; j++ );
	}
	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;
	if ( semop ( semid, sops, 1 ) < 0 )
		do_exit ( 3, "semop failed\n" );
	return 0;
}
