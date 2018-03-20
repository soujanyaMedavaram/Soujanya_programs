# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "stack.h"

struct stack {
	int size;
	int fd;
};

STACK * stack_open ( int nitems, int size ) {
	STACK * sd;
	int sp, exists;

	sd = malloc ( sizeof ( STACK ) );
	sd->size = size;
	if ( access ( "stack.dat", F_OK ) == 0)
		 exists = 1;
	else exists = 0;
	sd->fd = open ( "stack.dat", O_CREAT | O_RDWR, 0600 );
	if ( sd->fd == -1 ) {
		printf ( "stack file cannot be created\n" );
		exit ( 1 );
	}
	if ( !exists ) {
		sp = sizeof (int);
		write ( sd->fd, & sp, sizeof(int) );
	}
	return sd;
}

int push ( STACK * sd, char * data ) {
	int sp;

	lseek ( sd->fd, 0, SEEK_SET );
	if ( read ( sd->fd, & sp, sizeof(int) ) != sizeof(int) )
		return S_EMPTY;
	lseek ( sd->fd, sp, SEEK_SET );
	write ( sd->fd, data, sd->size );
	sp += sd->size;
	lseek ( sd->fd, 0, SEEK_SET );
	write ( sd->fd, & sp, sizeof(int) ); 
	return S_SUCCESS;
}

int pop ( STACK * sd, char * data ) {
	int sp;

	lseek ( sd->fd, 0, SEEK_SET );
	read ( sd->fd, & sp, sizeof(int) );
	if ( sp <= sizeof(int) )
		return S_EMPTY;
	sp -= sd->size;
	lseek ( sd->fd, sp, SEEK_SET );
	read ( sd->fd, data, sd->size );
	lseek ( sd->fd, 0, SEEK_SET );
	write ( sd->fd, & sp, sizeof(int) );
	return S_SUCCESS;
}

int stack_full ( STACK * sd ) {
	return 0;
}

int stack_empty ( STACK * sd ) {
	int sp;

	lseek ( sd->fd, 0, SEEK_SET );
	read ( sd->fd, & sp, sizeof(int) );
	if ( sp <= sizeof(int) )
		return 1;
	return 0;
}

void close_stack ( STACK * sd )
{
	close ( sd->fd );
	free ( sd );
}

int stack_transient ( STACK * sd ) {
	return 0;
}
