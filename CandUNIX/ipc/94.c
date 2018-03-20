# include <stdio.h>
# include <sys/file.h>
# define MAXBUFF 10
# define SEQFILE "rs18.c"

void my_lock ( int fd ) {
	lseek ( fd, 0L, 0 );
	if ( lockf ( fd, F_LOCK, 0L) == -1 )
		fprintf ( stderr, "cna't F_LOCK" );
}

void my_unlock ( int fd ) {
	lseek ( fd, 0L, 0 );
	if ( lockf ( fd, F_ULOCK, 0L) == -1 )
		fprintf ( stderr, "cna't F_ULOCK" );
}
main  ( ) {
	int fd, i, n, pid, seqno;
	char buff[MAXBUFF + 1];

	pid = getpid ( );
	if ( (fd = open ( SEQFILE, 2 )) < 0 )
		 printf ( "can't open %s", SEQFILE );
	for ( i = 0; i < 20; i++ ) {
		my_lock ( fd );
		lseek ( fd, 0L, 0 );
		if ( (n = read ( fd, buff, MAXBUFF )) <= 0 )
			printf ( "read error" );
		buff[n] = '\0';
		if ( ( n = sscanf ( buff, "%d\n", &seqno)) != 1 )
			printf ( "sscanf error" );
		printf ( "read:pid = %d, seq# = %d\n", pid, seqno );
		seqno++;
		sprintf ( buff, "%03d\n", seqno );
		n = strlen ( buff );
		lseek ( fd, 0L, 0 );
		if ( write ( fd, buff, n) != n )
			printf ( "write error" );
		my_unlock ( fd );
	}
}


