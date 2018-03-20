#include <stdio.h>
#include "aqueue.h"

char *malloc (int);

AQUEUE * openQa(int nmax, int size)
{
	register AQUEUE *aqd;
	if (nmax < 1 || size < 1) return AQ_FAIL;
	aqd = (AQUEUE *)malloc(sizeof(*aqd) + nmax *size - 1);
	if (aqd == NULL) return AQ_FAIL;
	Head = Beg;
	Tail = Beg;
	End = Beg + nmax * size;
	Nitems = 0;
	aqd->nmax = nmax;
	Size = size;
	Nfree =  nmax * size;
	return aqd;
}

int enQa (register AQUEUE *aqd, char *data, int size)
{
	register int cut_piece;
	int temp = Size;
	if ( size < 1 || size > 255) return AQ_TOO_BIG;
	if ( (size + 1) > Nfree ) return  AQ_NO_SPACE;
	//*Tail++ = (unsigned char) size;
	while (temp != 0)
	{
		*Tail++ = *data++;
		if (Tail >= End) Tail = Beg;
		temp--;
	}
	Nitems++;
	Nfree -= size + 1;
	return AQ_SUCCESS;
}

int deQa(register AQUEUE *aqd, char *data) 
{
	register int cut_piece;
	int size, temp;
	if (!Nitems) return AQ_EMPTY;
	Nitems--;
	//size = (unsigned char) *Head++;
	temp = Size;
	Nfree -= size + 1;
	while (temp != 0)
	{
		*data++ = *Head++;
		if (Head >= End) Head = Beg;
		temp--;
	}

	return AQ_SUCCESS;
}

int closeQa(AQUEUE *aqd)
{
	free(aqd);
	return AQ_SUCCESS;
}
