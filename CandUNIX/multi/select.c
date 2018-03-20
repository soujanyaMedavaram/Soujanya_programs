# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX	200

char line[MAX];

main() {
	FILE *in2;
	FILE *in1;
	int nmax;
	fd_set fd_list;
	int retval;
	char *p;
	char *other;
	char * other_device (void);

	in1 = stdin;
	other = other_device ();
	if (other == NULL) {
		fprintf (stderr, "Please log on another terminal & then run this\n");
		exit (1);
	}
	in2 = fopen (other, "r");
	if (in2 == NULL) {
		fprintf (stderr, "Cannot open the other terminal device\n");
		exit (1);
	}
	nmax = fileno (in2);
	printf ("fd of other terminal = %d\n", nmax);
	printf ("Type a line on one of the terminals\n");
	FD_ZERO (&fd_list);
	FD_SET (0, &fd_list);
	FD_SET (nmax, &fd_list);
	retval = select (nmax + 1, &fd_list, NULL, NULL, NULL);
	printf ("Out of select :%d\n", retval);
	if (retval == -1 || retval == 0) {
		fprintf (stderr, "Could not do select properly\n"); exit (2);
	}
	if (FD_ISSET (0, &fd_list))
		 p = fgets (line, MAX, in1);
	else p = fgets (line, MAX, in2);
	if (p)
		printf ("Line read:%s", line);
}
