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
void open_dir(char *dir);

int stat(const char *,struct stat *);
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

int j = 0;

void details(char *dir)
{
	struct stat stbuf;
	int i;
	char dir_name[10][102], line[100], *name;
	struct dirent *dp;
	DIR *dfd;

	if ( ( dfd = opendir(dir) ) == NULL ) {
		fprintf ( stderr, "can not open the file %s\n", dir );
		fprintf ( stderr, "<%s>\n", strerror(errno) );
		return;
	}
	while ( (dp = readdir(dfd)) != NULL ) {
		if ( !strcmp(dp->d_name,"." ) || !strcmp(dp->d_name,".." ) )
			continue;
		name = malloc (strlen ( dir ) + strlen ( dp->d_name ) + 2 );
		strcpy ( name, dir );
		strcat ( name, "/" );
		strcat ( name, dp->d_name );
		if ( stat ( name, &stbuf ) == -1 ) {
			printf ( "stat failed %d\n", errno );
			continue;
		}
		if ( R_flag == 1 ) { 
			if ( S_ISDIR ( stbuf.st_mode ) ) {
				j++;
				printf ("\n%s/%s\n",dir,dp->d_name);
				chdir(dp->d_name);
				system ( "pwd" );
				details ( "." );
				chdir("..");
			}
		}
		if ( l_flag == 1 ) { 
			if ( S_ISDIR ( stbuf.st_mode ) ) 
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
			printf ( "%s  ", getpwuid ( getuid() ) ->pw_name );
			printf ( "%s  ", getgrgid ( getgid() ) -> gr_name );
			printf ( "  %ld", stbuf.st_size );
			strcpy ( line,ctime ( &stbuf.st_mtime ) );
			print_time ( line );
		}
		if ( i_flag == 1 )
			printf ( "%8ld\t", stbuf.st_ino );
		printf ( "  %s\n",dp->d_name );
	}
	closedir ( dfd );
}
