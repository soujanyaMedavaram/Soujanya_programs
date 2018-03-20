typedef struct
{
	int nmax;
	int size;
	char *end;
	char *ep;
	char *dp;
	char beg[1];
}QUEUE;

QUEUE * openQ( int nmax, int size);
int enQ ( QUEUE *qd, char *item);
int deQ ( QUEUE *qd, char *item);
int closeQ ( QUEUE *qd);
int Qfull(QUEUE *qd);
int Qempty(QUEUE *qd);

//# define Qfull(qd)		((qd->ep + qd->size) == qd->dp)
//# define Qempty(qd)		((qd->dp + 2 * qd->size) == (qd->ep + qd->size))
//#define Qempty(qd)			(qd->dp == qd->ep)

# define Q_SUCCESS 0
# define Q_FAIL NULL
# define Q_FULL -1
# define Q_EMPTY -2

