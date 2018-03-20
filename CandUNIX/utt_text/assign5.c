# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main ( ) {
	int fd;
	char *word, c;
	int i;

	switch ( fork ( ) ) {
		case -1:
				fprintf ( stderr, "fork failed \n" );
				exit ( 1 );
		case 0:
				fd = open ( "temptime", O_CREAT | O_TRUNC | O_RDWR, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "open failed\n");
					exit ( 1 );
				}
				close ( 1 );
				if ( dup ( fd ) != 1 ) {
					fprintf ( stderr, "dup failed \n" );
					exit ( 2 );
				}
				close ( fd );
				execlp ( "date", "date", NULL );
				fprintf ( stderr, "exec failed\n" );
				exit ( 4 );
	}
	switch ( fork ( ) ) {
		case -1 : 
				fprintf ( stderr, "fork failed \n" );
				exit ( 5 );
		case 0:
				fd = open ( "temptime", O_RDONLY, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "open failed \n" );
					exit ( 6 );
				}
				close ( 0 );
				lseek ( fd, 11, SEEK_SET );
				word = malloc ( 2 );
				read ( fd, word, 2 );	
				i = atoi ( word );
				if ( i >=0 && i <= 12 )
					printf ( " good morning \n" );
				else if ( i > 12 && i <= 17 )
					printf ( "good afternoon " );
				else 
					printf ( "good night" );
				close ( fd );
				break;
	}
}
