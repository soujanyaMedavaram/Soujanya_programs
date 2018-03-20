# include <stdio.h>
# include <signal.h>
# include <sys/sem.h>
# include <sys/ipc.h>
# include "../../sb.h"
# include <unistd.h>

main ( ) {
	FILE *fp;
	int pid;

	if ( access ( "sb_pid", F_OK ) )
		do_exit ( 1, "Database is not startedup\n" );
	fp = fopen ( "sb_pid", "r" );
	if ( fp == NULL )
		do_exit ( 2 , "No read permission in the current directory\n" );
	fscanf ( fp, "%d", &pid );
	fclose ( fp );
	system ( "rm -f sb_pid" );
	kill ( pid, SIGUSR1 );
}
