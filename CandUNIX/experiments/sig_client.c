# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

main ( ) {
	int p_id;
	FILE *fp;

	printf ( "client pid = %d\n", getpid () );
	fp = fopen ( "ser_pid", "r" );
	fscanf ( fp, "%d",&p_id );
	kill ( p_id, SIGCHLD );
}
