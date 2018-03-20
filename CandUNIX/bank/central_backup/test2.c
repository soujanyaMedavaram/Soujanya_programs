# include <stdio.h>
# include <sys/shm.h>
# include <errno.h>
# include <sys/ipc.h>

main  ( ) {
	int shmid;
	shmid = shmget ( getuid ( ), 200, 0600 | IPC_CREAT );
	if ( shmctl ( shmid, IPC_RMID, 0 ) < 0 )
		printf ( "<<<<<<<<%s\n", strerror ( errno ) );
	
	if ( shmctl ( shmid, IPC_RMID, 0 ) < 0 )
		printf ( "%s>>>>>>\n", strerror ( errno ) );
}
