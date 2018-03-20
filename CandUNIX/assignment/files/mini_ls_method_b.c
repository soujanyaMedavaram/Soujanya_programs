# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>

void details(char *name);

int stat(const char *,struct stat *);
char **dir_name;
int indx;

void print_time(char line[])
{
	char *p;
	int start;
	p = strchr(line,' ');
	start = p - line;
	*(strrchr(line,':')) = '\0';
	printf (" %s",start+line);
}

int l_flag = 0 , R_flag = 0, i_flag = 0;

main (int argc, char *argv[]) {
	int dir_found = 0;

	indx = 0;
	dir_name = (char **)malloc(sizeof(char *)*50 );
	while(*++argv) {
		if (**argv == '-') {
			while(*++*argv) {
				if(**argv == 'l')
					l_flag = 1;
				else if (**argv == 'R')
					R_flag = 1;
				else if (**argv == 'i')
					i_flag = 1;
				else {
					printf ("\n in valid argument\n");
					exit(1);
				}
			}
			continue;
		}
		dir_found = 1;
		details(*argv);
	}
	if (dir_found == 0)
		details(".");
	exit(0);
}

void details(char *dir)
{
	struct stat stbuf;
	int i, j;
	char line[100], *name;
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf (stderr, "can not open the file %s\n",dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (!strcmp(dp->d_name,".") || !strcmp(dp->d_name,".."))
			continue;
		name = malloc ( strlen (dp->d_name) + strlen (dir) + 2 );
		strcpy ( name, dir );
		strcat ( name, "/" );
		strcat ( name, dp->d_name );
		if ( stat(name, &stbuf) == -1) {
			printf ( "stat failed : %s\n", dp->d_name );
			continue;
		}
		if (R_flag == 1) 
			if (S_ISDIR(stbuf.st_mode))
				dir_name[indx++] = strdup (name);
		if (l_flag == 1) {
			if (S_ISDIR(stbuf.st_mode)) 
				putchar ( 'd' );
			else putchar ( '-' );
			putchar ( stbuf.st_mode & S_IRUSR ? 'r' : '-' );
			putchar ( stbuf.st_mode & S_IWUSR ? 'w' : '-' );
			putchar ( stbuf.st_mode & S_IXUSR ? 'x' : '-' );
			putchar ( stbuf.st_mode & S_IRGRP ? 'r' : '-' );
			putchar ( stbuf.st_mode & S_IWGRP ? 'w' : '-' );
			putchar ( stbuf.st_mode & S_IXGRP ? 'x' : '-' );
			putchar ( stbuf.st_mode & S_IROTH ? 'r' : '-' );
			putchar ( stbuf.st_mode & S_IWOTH ? 'w' : '-' );
			putchar ( stbuf.st_mode & S_IXOTH ? 'x' : '-' );
			printf ( "  %d  ",stbuf.st_nlink );
			printf ( "%s  ",getpwuid ( getuid() ) ->pw_name );
			printf ( "%s  ", getgrgid(getgid()) -> gr_name );
			printf ("  %6ld",stbuf.st_size);
			strcpy(line,ctime(&stbuf.st_mtime));
			print_time(line);
		}
		if (i_flag == 1)
			printf ("%8ld\t", stbuf.st_ino);
		printf ("  %s\n",dp->d_name);
	}
	closedir(dfd);
	if (R_flag == 1 && indx > 0) {
		j = indx;
		indx = 0;
		for (i = 0; i < j; i++) {
			printf ("\n ==== %s ====\n", dir_name[i]);
			details (dir_name[i]);
		}
		for (i = 0; i < j; i++)
			free ( dir_name[i] );
	}
}
