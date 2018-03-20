struct item
{
	struct item *next;
	struct item *prev;
	char data[1];
};

typedef struct
{
	struct item *first;
	struct item *last;
	struct item *transferred;
	long magic;
	int size;
	int nitems;
	long ntrans;
	int dir;


# define FORWARD 0
# define REVERSE 1

	int transfer_flag;
}LIST;
	
# define L_SUCCESS	0
# define L_EMPTY	1
# define L_NO_MORE	2
# define L_ILLEGAL	3
# define L_NOT_READ	4
# define L_FAIL		NULL

# define First			ld->first
# define Last			ld->last
# define Transferred	ld->transferred
# define Magic			ld->magic
# define Size			ld->size
# define Nitems			ld->nitems
# define Dir			ld->dir
# define Transfer_flag	ld->transfer_flag
# define Ntrans			ld->ntrans
# define Next			item->next
# define Prev			item->prev
# define Data			item->data

# define	list_empty(ld)			!Nitems
# define	ntransactions(ld)		Ntrans
# define	reset_transferred(ld)	Transferred = NULL

LIST * open_list(int size);
int close_list(LIST *ld);
int append(LIST *ld, char *data);
int read_first(LIST *ld, char *data);
int read_last(LIST *ld, char *data);
int read_next(LIST *ld, char *data);
int read_prev(LIST *ld, char *data);
int delete(LIST *ld);

