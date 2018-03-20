# include <stdio.h>
# include <signal.h>

static void handler ( int signum, siginfo_t *info,void *context ) {
	printf ( " IN signal handler \n" );
	printf ( " signal received = %d\n", signum );
	printf ( " signal num = %ld\n", info->si_signo );
	printf ( " process id = %ld\n", info->si_pid );
}

main  ( ) {
	struct sigaction act;
	union sigval val;
	FILE *fp;

	fp = fopen ( "server_pid", "w" );
	if ( fp == NULL ) {
		fprintf ( stderr, "fail to open server file\n" );
		exit ( 1);
	}
	printf ( " server pid = %ld\n", getpid ( ) );
	fprintf ( fp, "%ld", getpid ( ) );
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler ;
	sigaction ( SIGPOLL, &act, NULL );
	fclose ( fp );
	//close ( 0 ); close ( 1  ); close ( 2  );
	pause ( );
}
