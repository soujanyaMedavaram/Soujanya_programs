# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>

main (  ) {
	struct stat buf;
	if ( stat ( "nclient.c", &buf ) == -1 )
	{
		printf ( "stat failed \n" );
		exit ( 1  );
	}
	printf ( "<%d>\n", buf.st_mtime );
	printf ( "<%s>\n", ctime ( &buf.st_mtime ) );
	printf ( "hai" );
}
