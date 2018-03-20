# include <stdio.h>
# include "stack.h"
# include <stdlib.h>

struct s_item
{
	struct s_item *next;
	struct s_item *prev;
	char data[1];
};

struct stack {
	struct s_item *sp;
	int size;
	int nitems;
	long ntrans;
};

# define	Sp		sld->sp
# define	Size	sld->size
# define	Nitems	sld->nitems
# define	Ntrans	sld->ntrans
# define	Data	s_item->data
# define	Next	s_item->next
# define	Prev	s_item->prev

STACK	*stack_open ( int nitems, int size ) {
	register STACK *sld;
	
	if ( size < 1 ) return S_FAIL;
	sld =  (STACK *)malloc (sizeof (*sld) ) ; 
	if ( sld == NULL )
		return S_FAIL;
	Sp = NULL;
	Size = size;
	Nitems = 0;
	return sld;
}

int push ( register STACK	*sld, char *data ) {
	struct s_item *s_item;

	s_item = ( struct s_item *)malloc (sizeof(*s_item) + Size - 1 );
	memcpy ( Data, data , Size );
	Next = NULL;
	Prev = NULL;
	if ( Nitems > 0 ) {
		Sp->next = s_item;		// sld->sp->next = s_item;
		Prev = Sp;
	}
	Sp = s_item;
	Nitems++;
	return S_SUCCESS;
}

int pop ( register STACK *sld , char *data) {
	struct s_item *sitem, *temp;

	memcpy ( data, Sp->data, Size );
	temp = Sp;
	Sp = Sp->prev;
	Nitems--;
	free(temp);
	return S_SUCCESS;
}
void close_stack (register STACK *sld ) {
	free((char *)sld);
}

int stack_full (register STACK *sld ) {
	return 0;
}
int stack_empty (register STACK *sld) {
	return Nitems == 0;
}
