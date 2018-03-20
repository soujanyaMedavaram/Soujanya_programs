# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main ( ) {
	int fd;
	char word[10] = "hai";
	fd = open (word, O_CREAT | O_TRUNC | O_WRONLY,600);
	if ( fd < 0 ) {
		fprintf ( stderr, "open failed\n" );
		exit ( 1 );
	}
	else
		printf ( "open success\n" );
	close ( fd );
}
