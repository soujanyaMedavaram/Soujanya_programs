# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX	200

char line[MAX];

	FILE *in2;
	FILE *in1;
	int fd;
	fd_set fd_list;
	int retval;
	char *p;
	void sig_poll (int);
	int flags;
	int counter;
	char *other;
	char *other_device (void);

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

	signal (SIGPOLL, sig_poll);
	printf ("Type lines on one of the terminals\n");
	for (counter = 0; ;)
		if (counter == 9999) counter = 0;
		else counter++;
}

void sig_poll (int signo) {
//	printf ("Received signal %d\n", signo);
	FD_ZERO (&fd_list);
	FD_SET (0, &fd_list);
	FD_SET (fd, &fd_list);
	retval = select (fd + 1, &fd_list, NULL, NULL, NULL);
//	printf ("Out of select :%d\n", retval);
	if (retval == -1 || retval == 0) {
		fprintf (stderr, "Could not do select properly\n"); exit (2);
	}
	if (FD_ISSET (0, &fd_list))
		 p = fgets (line, MAX, in1);
	else p = fgets (line, MAX, in2);
	if (p)
		printf ("Counter = %d  Line read:%s", counter, line);
	signal (SIGPOLL, sig_poll);
}
