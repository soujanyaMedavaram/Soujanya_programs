# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define datafile "hai"

void fun ( char *msg ) {
	fprintf ( stderr, "%s", msg );
}

main ( ) {
	int fd;
	if ( access ( datafile, F_OK )  ) 
		fd = open ( datafile, O_CREAT ,0600);
	else 
		fd = open ( datafile, O_APPEND ); 
	printf ( "%d->fd\n", fd );
	fun ( "hai uttara\n" );
	fun ( "hello\n" );
	close ( fd );
	return 0;
}
