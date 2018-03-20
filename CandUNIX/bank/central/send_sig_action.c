# include <stdio.h>
# include <signal.h>

main  ( ) {
	FILE *fp;
	long pid;
	printf ( " sending process id = %ld\n", getpid ( ) );
	fp = fopen ( "server_pid", "r" );
	if ( fp == NULL ) {
		fprintf ( stderr, "file open failed\n" );
		exit ( 1  );
	}
	fscanf ( fp, "%d", &pid );
	printf ( " server pid in client %ld\n", pid );
	printf ( " signal sendin\n" );
	kill ( pid, SIGPOLL );
}
