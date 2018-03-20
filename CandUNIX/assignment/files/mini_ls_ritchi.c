# include <stdio.h>
# include <sys/types.h>
//# include "syscalls.h"
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

void details(char *name);
void dirwalk (char *, void (*fcn)(char *));

int stat(const char *, struct stat *);

main (int argc, char *argv[]) {
	if (argc == 1)
		details(".");
	else
		while (--argc) 
			details(*++argv);
	return 0;
}

void details (char *name)
{
	struct stat stbuf;
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, details);
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "Details: can't access %s \n", name);
		return;
	}
	printf ("%8ld %s \n", stbuf.st_size, name);
}

# define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) != NULL) {
		fprintf(stderr, "dirwalk: can't open %s \n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
		|| strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(dp->d_name))
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
		else {
			sprintf (dp->d_name, "%s/%s",dir, dp->d_name);
			(*fcn)(dp->d_name);
		}
	}
	closedir(dfd);
}
