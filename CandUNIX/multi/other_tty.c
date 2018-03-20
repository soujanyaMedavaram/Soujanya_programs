/*	find another terminal on which user is logged in.
	Returns NULL if not.  */

# define LENGTH		100

# include <stdio.h>

char * other_device () {
	char * malloc (int);
	char * device, * device1;
	char * line;
	char * p, * q;
	char * user, * user1;
	FILE *fp;

	line = malloc (LENGTH);
	device = malloc (LENGTH);
	device1 = malloc (LENGTH);
	user = malloc (LENGTH);
	user1 = malloc (LENGTH);
	fp = popen ("who am i", "r");
	if (fp == NULL) {
		fprintf (stderr, "Cannot run <who am i> command\n"); exit (1);
	}
	while (fgets (line, LENGTH, fp)) {
		p = line;
		if (!*p) {
			fprintf (stderr, "Output of <who am i> is not okay\n"); exit (2);
		}
		q = user;
		while (*p != ' ' && *p != '\t') *q++ = *p++;
		*q = '\0';
		while (*p == ' ' || *p == '\t') p++;
		strcpy (device, "/dev/");
		q = device + strlen (device);
		while (*p != ' ' && *p != '\t') *q++ = *p++;
		*q = '\0';
	}
	fclose (fp);
	fp = popen ("who", "r");
	if (fp == NULL) {
		fprintf (stderr, "Cannot run <who> command\n"); exit (1);
	}
	while (fgets (line, LENGTH, fp)) {
		for (p = line; *p == ' ' || *p == '\t'; p++) ;
		q = user1;
		while (*p != ' ' && *p != '\t') *q++ = *p++;
		*q = '\0';
//		printf ("user:<%s>  user1:<%s>\n", user, user1);
		if (strcmp (user, user1)) continue;
		while (*p == ' ' || *p == '\t') p++;
		strcpy (device1, "/dev/");
		q = device1 + strlen (device1);
		while (*p != ' ' && *p != '\t') *q++ = *p++;
		*q = '\0';
		if (!strcmp (device, device1)) continue;
		free (device); free (user); free (user1); free (line);
		return device1;
	}
	free (device); free (user); free (user1); free (line);
	return NULL;
}
