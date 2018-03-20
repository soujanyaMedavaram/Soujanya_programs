typedef struct
{
	int nmax;
	int size;
	int nitems;
	char *end;
	char *ep;
	char *dp;
	char *beg;
}QUEUE;

QUEUE * openQ(int size);
int enQ ( QUEUE *qd, char *item);
int deQ ( QUEUE *qd, char *item);
int closeQ ( QUEUE *qd);

# define Qfull(qd)		(qd->nitems == qd->nmax)
# define Qempty(qd)		(qd->nitems == 0)

# define Q_SUCCESS 0
# define Q_FAIL NULL
//# define Q_FULL -1
# define Q_EMPTY -2

