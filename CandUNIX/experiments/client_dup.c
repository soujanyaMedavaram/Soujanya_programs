# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

main ( ) {
	int fd_r, fd_w;
	mkfifo ( "clififo", O_CREAT | 0600 );
	fd_r = open ( "clififo", O_WRONLY );
	printf ( "hai\n" );
}

