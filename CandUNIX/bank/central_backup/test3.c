# include <stdio.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

main  ( ) {
	int fd1, fd2, i;
	fd_set fd_list;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	fd1 = open ( "/etc/passwd", O_RDONLY );
	fd2 = open ( "/etc/group", O_RDONLY );
	FD_ZERO ( &fd_list );
	for ( i = 3; i < 10; i++ );
	FD_SET ( i, &fd_list );
	select ( 8, &fd_list, NULL, NULL, &tv );
	for ( i = 0; i < 10; i++ ) {
		printf ( "\n Inside for loop \n" );
		printf ( "%d->FD_ISSET\n", FD_ISSET ( i, &fd_list ) );
		if ( FD_ISSET ( i, &fd_list ) )
			printf ( "%d is member of fd_list\n", i );
	}
	printf ( " program end\n" );
	close ( fd1 );
	close ( fd2 );
}

