# include<stdio.h>
# include"queuea.h"

char * malloc (int);
int free (char *);

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
	return qd;
}
int Qfull(QUEUE *qd)
{
	char *x;
	x = qd->ep;
	if((x += qd->size) >= qd->end)
		x = qd->beg;
	if (x == qd->dp)
		return 1;
	else return 0;
}
int Qempty(QUEUE *qd)
{
	return qd->dp == qd->ep;
}
int enQ (register QUEUE *qd, char *item)
{
	if (Qfull(qd)) return Q_FULL;
	memcpy (qd->ep,item,qd->size);
	if ((qd->ep += qd->size) >= qd->end )
		qd->ep = qd->beg;
	return Q_SUCCESS;
}

int deQ (register QUEUE *qd, char *item)
{
	if (Qempty(qd)) return Q_EMPTY;
	memcpy (item, qd->dp,qd->size);
	if ( (qd->dp += qd->size) >= qd->end)
		qd->dp= qd->beg;
	return Q_SUCCESS;
}

int closeQ(QUEUE *qd)
{
	free((char *)qd);
	return Q_SUCCESS;
}

