# include <stdio.h>
# include "queue.h"
struct q_item {
	struct q_item	*next;
	char data[1];
};

struct queue{
	struct q_item *front;
	struct q_item *rear;
	char *beg;
	char *end;
	int nitems;
	int max;
	int size;
};

# define	Front	qd->front
# define	Rear	qd->rear
# define	Beg		qd->beg
# define	End		qd->end
# define    Nitems	qd->nitems	
# define	Max		qd->max
# define	Size	qd->size
# define	Next	qitem->next
# define 	Data	qitem->data

QUEUE	*openQ ( int max, int size ) {
	QUEUE	*qd;
	qd = ( QUEUE * )malloc ( sizeof (*qd) );
	if ( qd == NULL ) return Q_FAIL;
	Max = max;
	Size = size;
	Nitems = 0;
	Front = NULL;
	Rear = NULL;
	return qd;
}

int enQ ( register QUEUE *qd, char *data )
{
	struct q_item *qitem;
	qitem = ( struct q_item * ) malloc ( sizeof(*qitem) + Size - 1 );
	memcpy(Data, data, Size);
	Next = Front;
	if ( !Nitems )
		Front = qitem;
	else 
		Rear->next = qitem;
	Rear = qitem;
	Nitems++;
	return Q_SUCCESS;
}

int deQ ( register QUEUE *qd, char *data ) {
	struct q_item *qitem, *temp;
	memcpy(data,Front->data,Size);
	Front = Front->next;
	free (temp);
	Nitems--;
	return Q_SUCCESS;
}
int Qempty (QUEUE	*qd ) {
	return Nitems == 0 ;
}
int Qfull (QUEUE *qd ) {
	return Nitems == Max;
}
void closeQ ( register QUEUE *qd ) {
	free((char *)qd);
}
