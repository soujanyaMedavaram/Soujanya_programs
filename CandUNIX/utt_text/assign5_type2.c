# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

main ( ) {
	int fd, i;
	char *word;

	switch ( fork () ) {
		case -1:
				fprintf (stderr, "fork failed\n" );
				exit ( 1 );
		case 0: 
				system ( "date > temptime  " );
				
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
	wait (0) ;
}
