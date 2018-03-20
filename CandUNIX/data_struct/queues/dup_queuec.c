# include<stdio.h>
# include"queued.h"

#define ROQ 10

char * mallocd (int);
int free (char *);

QUEUE * openQ(int size)
{
	register QUEUE *qd;
	if (size < 1) return Q_FAIL;
	qd = (QUEUE *)malloc(sizeof(*qd) + ROQ * size - 1);
	if (qd ==NULL) return Q_FAIL;
	qd->dp = qd->beg;
	qd->ep = qd->beg;
	qd->end = qd->beg + ROQ * size;
	qd->size = size;
	qd->nitems = 0;
	return qd;
}

int enQ (register QUEUE **qd, char *item)
{
	static int m = 1;
	(*qd)->nitems++;
	if(!((*qd)->nitems % ROQ) )
	{
		(*qd) = (QUEUE *)realloc((*qd),m++ * ROQ * sizeof(*(*qd)));
		(*qd)->end = (*qd)->beg + (m++ * ROQ * sizeof(*(*qd)));
	}
	memcpy ((*qd)->ep,item,(*qd)->size);
	if (((*qd)->ep += (*qd)->size) >= (*qd)->end)
		(*qd)->ep = (*qd)->beg;
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

