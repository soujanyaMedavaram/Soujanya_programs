# include<stdio.h>
# include"queue.h"

char * malloc (int);
int free (char *);
struct queue
{
	int nmax;
	int size;
	int nitems;
	char *end;
	char *ep;
	char *dp;
	char beg[1];
};

QUEUE * openQ(int nmax, int size)
{
	register QUEUE *qd;
	if (nmax < 1 || size < 1) return Q_FAIL;
	qd = (QUEUE *)malloc(sizeof(*qd) + nmax * size - 1);
	if (qd ==NULL) return Q_FAIL;
	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + nmax * size;
	qd->nmax = nmax;
	qd->size = size;
	qd->nitems = 0;
	return qd;
}

int enQ (register QUEUE *qd, char *item)
{
	if (Qfull(qd)) return Q_FULL;
	memcpy (qd->ep,item,qd->size);
	if ((qd->ep += qd->size) >= qd->end)
		qd->ep = qd->beg;
	qd->nitems++;
	return Q_SUCCESS;
}

int deQ (register QUEUE *qd, char *item)
{
	if (Qempty(qd)) return Q_EMPTY;
	memcpy (item, qd->dp,qd->size);
	if ( (qd->dp += qd->size) >= qd->end ) qd->dp = qd->beg;
	qd -> nitems--;
	return Q_SUCCESS;
}

int Qfull ( QUEUE *qd ) {
	return qd->nitems == qd->nmax ;
}
int Qempty ( QUEUE *qd )
{
	return qd->nitems == 0;
}

int closeQ(QUEUE *qd)
{
	free((char *)qd);
	return Q_SUCCESS;
}

