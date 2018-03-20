# include <stdio.h>
# include <unistd.h>
# include "stack.h"

struct stack {
	FILE *sp;
	FILE *sp_file;
	int size;
};

# define Sp			sd->sp
# define Sp_file	sd->sp_file
# define Size		sd->size

STACK *stack_open ( int nitems, int size ) {
	STACK *sd;
	sd = ( STACK * ) malloc ( sizeof ( STACK ) );
	Size = size;
	Sp = fopen ( "data.dat", access ( "data.dat" , F_OK ) ? "w+" : "r+" );
	setbuf ( Sp, NULL );
	fseek ( Sp, 0, SEEK_END );
	if ( Sp == NULL ) {
		printf ( "\n file not opened:stack failed\n" );
		exit ( 1 );
	}
	Sp_file = fopen ( "spfile.data", access ( "spfile.dats", F_OK ) ? "w+" : "r+" );
	fprintf (Sp_file,"%d", ftell(Sp));
	return sd;
}

int push ( STACK *sd, char *data ) {
	long temp;
	fseek (Sp_file,0,SEEK_SET);
	fscanf (Sp_file,"%d", &temp);
	fseek (Sp, temp,SEEK_SET );
	fwrite ( data, Size, 1, Sp );
	fseek ( Sp_file, 0, SEEK_SET );
	fprintf (Sp_file, "%d",ftell(Sp));
	return S_SUCCESS;
}

int pop ( STACK *sd, char *data ) {
	long temp;
	fseek (Sp_file,0,SEEK_SET );
	fscanf ( Sp_file,"%d", &temp);
	fseek ( Sp, temp, SEEK_SET );
	if ( temp != 0)
	fseek ( Sp, -Size, SEEK_CUR );
	fread ( data, Size, 1, Sp );
	fseek ( Sp, -Size, SEEK_CUR );
	fseek (Sp_file,0,SEEK_SET);
	fprintf (Sp_file,"%d",ftell(Sp));
	return S_SUCCESS;
}

int stack_full ( STACK *sd ) {
	return 0;
}

int stack_empty ( STACK *sd ) {
	return ftell ( Sp ) == 0 ;
}

void close_stack ( STACK *sd )
{
	fclose (Sp);
	free ( (char *) sd );
}

int stack_transient (STACK *sd) {
	return 0;
}
