# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX	200

char line[MAX];
char *buf;

	FILE *in2;
	FILE *in1;
	int fd, sig_fd;
	fd_set fd_list;
	int retval;
	char *p;
	void sig_poll (int);
	int flags;
	int counter;
	char *other;
	char *other_device (void);
	struct sigaction sig_act;

void sig_action (int signo, siginfo_t *info, void *old ) ;

main() {
	in1 = stdin;

	other = other_device ();
	if (other == NULL ) {
		fprintf (stderr,"Log in another terminal and try\n");
		exit (1);
	}	
	in2 = fopen (other, "r");
	if (in2 == NULL) {
		fprintf (stderr, "Cannot open the other terminal device\n");
		exit (1);
	}
	fd = fileno (in2);
	fcntl (0, F_SETOWN, getpid());
	fcntl (fd, F_SETOWN, getpid());
	flags = fcntl (0, F_GETFL);
	fcntl (0, F_SETFL, flags | O_ASYNC);
	flags = fcntl (fd, F_GETFL);
	fcntl (fd, F_SETFL, flags | O_ASYNC);
	sig_act.sa_sigaction = sig_action;
	sig_act.sa_flags     = SA_SIGINFO ;
	//sig_act.sa_mask      = SA_NOMASK;
	sigaction (SIGPOLL, &sig_act, NULL );
	printf ("Type lines on one of the terminals\n");
	for (counter = 0; ;)
		if (counter == 9999) counter = 0;
		else counter++;
}

void sig_action (int signo, siginfo_t *info, void *old ) {

	sig_fd = info->si_fd;
	printf ( "%d->sig_fd\n", sig_fd );
	if ( sig_fd == 0 )
		 p = fgets ( line, MAX, in1 );
	else p = fgets ( line, MAX, in2 );
	if (p)
		printf ( "Counter = %d Line read:%s", counter, line );
	sigaction (SIGPOLL, &sig_act , NULL );
}
