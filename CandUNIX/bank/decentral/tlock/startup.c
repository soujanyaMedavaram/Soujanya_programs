# include <stdio.h>
# include <sys/sem.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <signal.h>

void catch (int sig) { 
	printf ( "I am signal handler\n" );
}

# define TMP_FILE	"./sb_pid"

int main ( ) {
	int semid;
	FILE * fp;

	if ( (semid = semget ( getuid() , 1, 0600 | IPC_CREAT | IPC_EXCL ) ) < 0 )
		do_exit ( 1, "Database already started up\n" );
	if ( semctl ( semid, 0, SETVAL , 1) < 0 )
		do_exit ( 3, "Cannot initialize semaphore\n" );
	signal ( SIGUSR1, catch );
	printf ( "Database started up\n" );
	switch ( fork() ) {
		case -1:
		case 0: break;
		default: exit ( 0 );
	}
	fp = fopen ( TMP_FILE, "w" );
	if ( fp == NULL )
		do_exit ( 4, "No write permission in current directory\n" );
	fprintf ( fp, "%d\n", getpid() );
	fclose ( fp );
	close ( 0 ); close ( 1 ); close ( 2 );
	pause ( );
	semctl ( semid, IPC_RMID, 0 );
	exit ( 0 );
}
