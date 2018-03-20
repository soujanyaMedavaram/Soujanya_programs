
	int num;

	while ( 1  ) {
		cout << " Enter a element :(-10 to stop ) ";
		is >> num;
		if ( num == -10 ) break;
		if ( list->nitems == 0 ) {
			list.beg = new [sizeof(Node)];
			list->previous = list.node = list.beg;
			(list->beg)->prev = NULL;
		}
		else {
			list->node = new [sizeof(Node)];
			node->prev = list.previous;
			list->previous = list->node;
		}
		(list->node)->next = NULL;
		(list->node)->data = num;
		list->nitems++;
	}
	return is;
