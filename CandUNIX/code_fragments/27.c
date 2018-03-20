# include <stdio.h>
# include <stdlib.h>

struct single {
	struct single *next;
	int data;
};

# define Next node->next
# define Data node->data


main ( ) {
	int num;
	struct single *node, *pnode, *beg;

	pnode = NULL;
	beg = NULL;
	printf ( "\n enter numbers enter -1 at end \n" );
	while ( num != -1 ) {
		scanf ( "%d", &num );
		node = malloc ( sizeof *node );
		if ( beg == NULL )
			beg = node;
		Data = num;
		Next = NULL;
		if ( pnode != NULL ) 
			pnode->next = node;
		pnode = node;
	}
	printf ( "\n elements in the list are \n" );
	for (node = beg; node->next != NULL; node = node->next ) 
		printf ( "%d\n", Data);
}



	
