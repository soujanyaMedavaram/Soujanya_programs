# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>

main ( int argc, char *argv[] ) {
	struct stat stbuf;
	struct stat dup;
	int i;

	if ( argc > 1 ) {
		for ( i =1; i < argc; i++ ) {
			if ( stat ( argv[i] , &stbuf ) == -1 ) {
				fprintf ( stderr, "stat failed \n" );
				exit ( 1 );
			}
			printf ( "mtime - %s of %s\n", ctime ( &stbuf.st_mtime ), argv[i]);
			//printf ( "mtime - %ld\n", stbuf.st_mtime );
			printf ( "ctime - %s\n", ctime ( &stbuf.st_ctime) );
			printf ( "atime - %s\n", ctime ( &stbuf.st_atime) );
			//printf ( "Time comparision\n" );
			if ( i > 1 ) {
				if ( stbuf.st_mtime  < dup.st_mtime )
					printf ( "\n target older\n" );
				else printf ( "\n target updated\n" );
			}
			dup = stbuf;
		}
	}
	else 
		fprintf ( stderr, "Usage: <file> <file> ..\n" );
	exit ( 0 );
}
	

