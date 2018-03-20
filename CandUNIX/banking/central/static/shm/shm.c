# include <stdio.h>
# include <sys/msg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../ipc.h"
# include <stdlib.h>

# define CH_MAX	100

void create_ipc ( int max_chl ) {
	int i, j;
	char channel[CH_MAX];

	fd_max = max_chl;
	fd = malloc ( max_chl * sizeof ( int * ) );
	for ( i = 0; i <= max_chl; i++ ) {
		sprintf ( channel, "FIFO%d", i );
		if ( mkfifo ( channel, 0600 ) < 0 && EEXIST != errno ) {
			for ( j = 0; j < i; j++ ) {
				sprintf ( channel, "FIFO%d", j );
				close ( fd[j] );
				unlink  ( channel );
			}
			do_exit ( 2, "creation of fifo failed\n" );
		}
		fd[i] = open ( channel, O_RDWR );
		if ( fd[i] < 0 ) {
			for ( j = 0; j < i; j++ ) {
				close ( fd[j] );
				sprintf ( channel, "FIFO%d", j );
				unlink ( channel );
			}
			do_exit ( 2, "creation of fifo failed\n" );
		}
	}
}

void read_request ( Request *req, int size ) {
	read ( fd[0], req, size );
}

void write_request ( Request *req, int size ) {
	printf ( "%s\n", (*req).cust_name );
	printf ( "%s\n", (*req).phone );
	write ( fd[0], req, size );
	printf ( "<%s>->error\n", strerror ( errno ) );
}

void write_reply ( reply *rep,  int size, int channel ) {
	write ( fd[channel], rep, size );
}
void read_reply ( int channel , reply *rep, int size ) {
	read ( fd[channel], rep, size );
}
void remove_ipc ( ) {
	int i;
	char channel[CH_MAX];
	close ( fd_db );
	for ( i = 0; i <= fd_max; i++ ) {
		close ( fd[i] );
		sprintf ( channel, "FIFO%d", i );
		unlink ( channel );
	}
}


				
	
	
	
