# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

main ( int argc, char *argv[] ) {
	int fd_r, fd_w;
	if ( *argv[1] == '1' ) {
	mkfifo ( "fifotest", O_CREAT | 600 );
	fd_w = open ( "fifotest", O_WRONLY );
	printf ( "\n hai hello\n" );
	fd_r = open ( "fifotest", O_RDONLY );
	printf ( "opened fifo\n" );
	}
	else
	unlink ( "fifotest" );

}
