# include<stdio.h>
# include <stdlib.h>
# include"queuec.h"

#define ROQ		5 

QUEUE * openQ(int size)
{
	register QUEUE *qd;
	qd = (QUEUE *)malloc(sizeof(*qd));
	if (qd ==NULL) return Q_FAIL;
	qd->beg = malloc(ROQ * size);
	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + ROQ * size;
	qd->size = size;
	qd->nitems = 0;
	return qd;
}

int enQ (register QUEUE *qd, char *item)
{
	static int m = 1;
	qd->nitems++;
	if ( !(qd->nitems % ROQ) )	
	{
		printf("\nworking realloc\n");
		printf ( "%d\n", sizeof ( *qd ) );
		qd->beg = realloc(qd->beg, m++ * ROQ * qd->size);
		qd->end = qd->beg + (m++ * ROQ * qd->size);
	}
	memcpy (qd->ep,item,qd->size);
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

