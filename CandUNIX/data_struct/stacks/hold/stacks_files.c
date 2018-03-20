# include <stdio.h>
# include "stack.h"

struct stack {
	FILE *sp;
	int nitems;
	int size;
};
# define Nitems		sd->nitems
# define Size		sd->size
# define Sp			sd->sp

STACK *stack_open ( int nitems, int size ) {
	STACK *sd;
	sd = ( STACK * ) malloc ( sizeof(STACK) );
	Sp =NULL;
	Nitems = 0;
	Size = size;
	return sd;
}

int push ( STACK *sd, char *data ) {
	static FILE *file_position;
	static fpos_t *ptr = NULL;
	Sp = fopen ( "file1.dat", "a" );
	if ( !Nitems )
		file_position = Sp;
	else
		fsetpos ( file_position, ptr );
	fprintf ( file_position, "%s",data);
	fprintf ( file_position, "\n" );
	fgetpos(file_position, ptr);
	fclose (Sp);
	Nitems++;
	return S_SUCCESS;
}

int pop ( STACK *sd, char *data ) {
	static FILE *file_position2;
	static fpos_t *ptr2 =NULL;
	int c;

	Sp = fopen ( "file1.dat", "a+");
	fseek (file_position2, -1, SEEK_END );
	if (ptr2 != NULL )
		fgetpos ( file_position2, ptr2 );
	while ( !(fseek(file_position2 , -1, 1)) && (c = getc(file_position2)) != '\n');
	fgetpos(file_position2, ptr2);
	fseek (file_position2, 1, 1);
	while ((c = getc(file_position2)) != '\n')
		*data++ = c;
	fclose (Sp);
	return S_SUCCESS;
}

int stack_full (STACK *sd ) {
	return 0;
}

int stack_empty (STACK *sd) {
	return Sp == NULL;
}

void close_stack(STACK *sd ) {
	fclose(Sp);
}
		
