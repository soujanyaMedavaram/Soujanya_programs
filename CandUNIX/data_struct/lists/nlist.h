struct item
{
	struct item *bigger;
	struct item *smaller;
	char data[1];
};

typedef struct
{
	struct item *smallest;
	struct item *biggest;
	struct item *transferred;
	struct item *temp;
	int (*compare)(char *,char *);
	long magic;
	int size;
	int nitems;
	long ntrans;
	int dir;
# define FORWARD	0
# define REVERSE	1
	int transfer_flag;
}LIST;

# define L_SUCCESS	0
# define L_EMPTY	1
# define L_NO_MORE	2
# define L_ILLEGAL	3
# define L_NOT_READ	4
# define L_FAIL		NULL

# define Smallest		ld->smallest
# define Biggest		ld->biggest
# define Transferred	ld->transferred
# define Temp			ld->temp
# define Compare		ld->compare
# define Magic			ld->magic
# define Size			ld->size
# define Nitems			ld->nitems
# define Dir			ld->dir
# define Transfer_flag	ld->transfer_flag
# define Bigger			item->bigger
# define Smaller		item->smaller
# define Data			item->data
# define Ntrans			ld->ntrans
	

# define list_empty(ld)			!Nitems
# define ntransactions(ld)		Ntrans
# define reset_transferred(ld)	Transferred = NULL

LIST *open_list (int size, int (*compare)());
int close_list (LIST *ld);
int insert_in_list (LIST *ld, char *data);
int read_smallest (LIST *ld, char *data);
int read_biggest (LIST *ld, char *data);
int read_bigger (LIST *ld, char *data);
int read_smaller (LIST *ld, char *data);
int delete (LIST *ld);
long tot_cal(LIST *ld);
double avg_cal(LIST *ld);
long stats_cal( LIST *ld);

