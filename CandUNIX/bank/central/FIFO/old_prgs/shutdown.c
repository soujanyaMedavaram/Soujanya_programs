# include <stdio.h>
# include "../../../sb.h"
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

main ( ) {
	int pid;
	FILE *fp;
	if ( access ( "ser_pid", F_OK ) )
		do_exit ( 1 , "Server not startedup\n" );
	fp = fopen ( "ser_pid", "r" );
	if ( fp == NULL )
		do_exit ( 2, "permission denied for 'ser_pid' in curent direcotry\n" );
	fscanf ( fp, "%d", &pid );
	system ( "rm -f ser_pid" );
	printf ( "server shutdown\n" );
	kill ( pid, SIGUSR1 );
}
