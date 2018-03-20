# include <stdio.h>
# include <stdlib.h>

struct single {
	struct single *next;
	int data;
};

# define Next node->next
# define Data node->data

typedef struct {
	struct single *pnode;
	struct single *beg;
	int size;
}LIST;

# define Beg 	list->beg
# define Pnode	list->pnode
# define Size	list->size

LIST * open_list ( int size ) {
	LIST *list;
	Beg = NULL;
	Pnode = NULL;
	Size = size;
	list = (LIST * )malloc ( sizeof(LIST) );
	return list;
}

main ( ) {
	int num;
	char *numb;
	struct single *node;
	setbuf ( stdout, NULL );

	printf ( "hai ");
	LIST *list = open_list ( sizeof(num) );
	printf ( "\n enter numbers enter -1 at end \n" );
	while ( num != -1 ) {
		scanf ( "%d", &num );
		node = malloc ( sizeof *node );
		if ( Beg == NULL )
			Beg = node;
		Data = num;
		Next = NULL;
		if ( Pnode != NULL ) 
			Pnode->next = node;
		Pnode = node;
	}
	printf ( "\n elements in the list are \n" );
	for (node = Beg; node->next != NULL; node = node->next ) 
		printf ( "%d\n", Data);
}



	
