# include<stdio.h>
# include"queuec.h"

#define ROQ		5 

char * malloc (int);
int free (char *);

QUEUE * openQ(int size)
{
	register QUEUE *qd;
	qd = (QUEUE *)malloc(sizeof(*qd));
	if (qd ==NULL) return Q_FAIL;
	qd->beg = malloc(ROQ * size);
	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + ROQ * size;
	qd->nmax = ROQ;
	qd->size = size;
	qd->nitems = 0;
	return qd;
}

int enQ (register QUEUE *qd, char *item)
{
	int diff_ep, diff_dp;

	if ( Qfull(qd) )	
	{
		printf ( "allocating maemory\n" );
		diff_dp = qd -> end - qd -> dp;
		diff_ep = qd -> ep - qd -> beg;
		qd->beg = (char *)realloc(qd->beg,(qd->nmax += ROQ )* sizeof(char *));
		qd->end = qd->beg + (qd->nmax * qd->size);
		if ( qd->ep == qd->beg && qd->dp == qd->beg )  {
			qd->ep = qd -> beg + diff_dp;
			qd -> dp = qd -> beg;
		}
		else {
			memmove ( qd -> end - diff_dp, qd -> beg + diff_ep, diff_dp );
			qd -> dp = qd -> end - diff_dp;
			qd -> ep = qd -> beg + diff_ep;
		}
	}
	memcpy (qd->ep,item,qd->size);
	qd->nitems++;
	if ((qd->ep += qd->size) >= qd->end)
		qd->ep = qd->beg;
	return Q_SUCCESS;
}

int deQ (register QUEUE *qd, char *item)
{
	if (Qempty(qd)) return Q_EMPTY;
	qd->nitems--;
	memcpy (item, qd->dp,qd->size);
	if ( (qd->dp += qd->size) >= qd->end ) qd->dp = qd->beg;
	return Q_SUCCESS;
}

int closeQ(QUEUE *qd)
{
	free((char *)qd);
	return Q_SUCCESS;
}

