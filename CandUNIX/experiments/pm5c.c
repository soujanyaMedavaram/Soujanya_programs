# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

int main () {
	int pfd[2];

	if (pipe (pfd) < 0) {
		fprintf (stderr, "Cannot create pipe. File table Full\n");
		exit (-1);
	}

	switch (fork ()) {
		case -1:
			fprintf (stderr, "cannot fork. sysytem fault\n");
			exit (-1);

		case 0:
		printf ( "  before close \n" );
			close (1);
		printf ( "  after close \n" );
			printf ( " in ls child\n" );
			if (dup (pfd[1]) < 0) {
				fprintf (stderr, "cannot DUP, ERROR\n");
				exit (3);
			}
			close (pfd[0]); close (pfd[1]); 
			printf ( "before execl \n" );
			execl ("/bin/ls", "ls", "-l", NULL);
			fprintf (stderr, "Cannot exec\n");
			exit (4);

		default:
		printf ( "%s>>>>>>>\n", strerror ( errno ) );
			printf ( " in default of ls \n" );
			wait ( 0 );
			break;
	} 
	switch (fork ()) {
		case -1:
			fprintf (stderr, "cannot fork. sysytem fault\n");
			exit (-1);

		case 0:
		printf ( "In child process of wc \n" );
			close (0);
			if (dup (pfd[0]) < 0) {
				fprintf (stderr, "cannot DUP, ERROR\n");
				exit (3);
			}
			close (pfd[0]);  close (pfd[1]);
			execl ("/usr/bin/wc", "wc", NULL);
			fprintf (stderr, "Cannot exec\n");
			exit (5);

		default:
			break;
	} 
	close (pfd[0]);
	close (pfd[1]);
	wait (0);
	exit (0); 
}
