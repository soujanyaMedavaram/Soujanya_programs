typedef struct
{
	char *head;
	char *tail;
	char *end;
	int size;
	int nfree;
	int nitems;
	int nmax;
	char beg[1];
}AQUEUE;

AQUEUE * openQa (int nmax, int size);
int enQa (register AQUEUE *aqd, char *data, int size);
int deQa (register AQUEUE *aqd, char *data);
int closeQa (AQUEUE *aqd);

#define aQfull(aqd)	(aqd->nitems == aqd->nmax)
#define aQempty(aqd)	(aqd->nitems == 0)

#define Beg		(aqd->beg)
#define End		(aqd->end)
#define Head	(aqd->head)
#define Size	(aqd->size)
#define Tail 	(aqd->tail)
#define Nfree	(aqd->nfree)
#define Nitems	(aqd->nitems)

#define AQ_SUCCESS 0
#define AQ_FAIL NULL
#define AQ_FULL -1
#define AQ_EMPTY -2
#define AQ_TOO_BIG -3
#define AQ_NO_SPACE -4
