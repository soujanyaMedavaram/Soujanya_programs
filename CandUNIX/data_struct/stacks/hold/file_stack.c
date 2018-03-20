# include <stdio.h>
# include <unistd.h>
# include "stack.h"

struct stack {
	FILE *sp;
	int size;
	long beg;
};

# define Sp			sd->sp
# define Sp_file	sd->sp_file
# define Size		sd->size
# define Beg		sd->beg

STACK *stack_open ( int nitems, int size ) {
	STACK *sd;
	sd = ( STACK * ) malloc ( sizeof ( STACK ) );
	Size = size;
	Sp = fopen ( "data.dat", access ( "data.dat" , F_OK ) ? "w+" : "r+" );
	Beg = ftell ( Sp );
	fseek ( Sp, 0, SEEK_END );
	if ( Sp == NULL ) {
		printf ( "\n file not opened:stack failed\n" );
		exit ( 1 );
	}
	return sd;
}

int push ( STACK *sd, char *data ) {
	fwrite ( data, Size, 1, Sp );
	return S_SUCCESS;
}

int pop ( STACK *sd, char *data ) {
	fseek ( Sp, -Size, SEEK_CUR );
	fread ( data, Size, 1, Sp );
	fseek ( Sp, -Size, SEEK_CUR );
	return S_SUCCESS;
}

int stack_full ( STACK *sd ) {
	return 0;
}

int stack_empty ( STACK *sd ) {
	return ftell ( Sp ) == Beg ;
}

void close_stack ( STACK *sd )
{
	Beg = ftell ( Sp );
	fclose (Sp);
	free ( (char *) sd );
}

