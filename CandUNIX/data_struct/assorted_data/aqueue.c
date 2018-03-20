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
	aqd->size = size;
	Nfree =  nmax * size;
	return aqd;
}

int enQa (register AQUEUE *aqd, char *data, int size)
{
	register int cut_piece;

	if ( size < 1 || size > 255) return AQ_TOO_BIG;
	if ( (size + 1) > Nfree ) return  AQ_NO_SPACE;
	*Tail++ = (unsigned char) size;
	if (Tail >= End) Tail = Beg;
	if(size >= (End - Tail))
	{
		cut_piece = End - Tail;
		memcpy (Tail, data, cut_piece);
		Tail = Beg;
		size -= cut_piece;
		data += cut_piece;

	}
	if (size)
	{
		memcpy(Tail, data, size);
		Tail += size;
	}
		Nitems++;
		Nfree -= size + 1;
		return AQ_SUCCESS;
}

int deQa(register AQUEUE *aqd, char *data) 
{
	register int cut_piece;
	int size;

	if (!Nitems) return AQ_EMPTY;
	Nitems--;
	size = (unsigned char) *Head++;
	Nfree -= size + 1;
	if (Head >= End) Head = Beg;
	if (size >= (End - Head))
	{
		cut_piece = End - Head;
		memcpy(data,Head,cut_piece);
		Head = Beg;
		data += cut_piece;
		size -= cut_piece;
	}

	if (size)
	{
		memcpy(data, Head,size);
		Head += size;
	}
	return AQ_SUCCESS;
}

int closeQa(AQUEUE *aqd)
{
	free(aqd);
	return AQ_SUCCESS;
}
