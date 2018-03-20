struct q_item {
	struct q_item	*next;
	char data[1];
};

typedef struct {
	struct q_item *front;
	struct q_item *rear;
	char *beg;
	char *end;
	int nitems;
	int max;
	int size;
}L_QUEUE;

# define	Front	qld->front
# define	Rear	qld->rear
# define	Beg		qld->beg
# define	End		qld->end
# define    Nitems	qld->nitems	
# define	Max		qld->max
# define	Size	qld->size
# define	Next	qitem->next
# define 	Data	qitem->data

	
