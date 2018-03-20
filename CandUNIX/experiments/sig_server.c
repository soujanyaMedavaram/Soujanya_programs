# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

//siginfo_t *info;

static void fcn ( int signum, siginfo_t info , void *a ) {
	printf ( "Hello\n" );
	//info = malloc ( sizeof ( info ));
	printf ( "In signal handler: uid %d\n", info.si_uid );
	printf ( "In signal handler: pid %d\n", info.si_pid );
}

main  ( ) {
	struct sigaction act;
	FILE *fp;
	int ret_val;

	memset ( &act, 0, sizeof ( act ) );
	printf ( "%d->sigio\n", SIGIO );
	printf ( "%d->userid\n", getuid ( )  );
	act.sa_sigaction = fcn;
	act.sa_flags = SA_SIGINFO;
	ret_val = sigaction ( SIGCHLD, &act, NULL );
	fp = fopen ( "ser_pid", "w" );
	fprintf ( fp, "%d", getpid ( ) );
	printf ( "%d->server pid\n", getpid (  ) );
	fclose ( fp );
	pause ( );
	printf ( "ret_val = %d\n", ret_val );
}

