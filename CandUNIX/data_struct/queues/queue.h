typedef struct queue QUEUE;

QUEUE * openQ( int nmax, int size);
int enQ ( QUEUE *qd, char *item);
int deQ ( QUEUE *qd, char *item);
void closeQ ( QUEUE *qd);

# define Q_SUCCESS 0
# define Q_FAIL NULL
# define Q_FULL -1
# define Q_EMPTY -2

