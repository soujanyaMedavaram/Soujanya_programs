#include <stdio.h>
#include "buffer.h"

char *malloc(int);
//int free(char *);

BUFFER *create_buf (int size, int nmax)
{
	register BUFFER *bd;
	if (size < 1)	return BUF_FAIL;
	bd = (BUFFER *)malloc (sizeof (*bd) + nmax * size );
	if (bd == NULL) return BUF_FAIL;
	Nmax = nmax;
	Nchars = 0;
	Write = Beg;
	Read = Beg;
	End = Beg + nmax * size;
	return bd;
}

int write_buf (BUFFER *bd, char data)
{
	if (Nchars == Nmax) return BUF_FULL;
	*Write++ = data;
	Nchars++;
	if (Write > End) Write =Beg;
	return BUF_SUCCESS;
}

int read_buf (BUFFER *bd)
{
	if (Nchars == 0) return BUF_EMPTY;
	printf("%d\n",*Read);
	*Read++;
	Nchars--;
	if (Read > End) Read = Beg;
	return BUF_SUCCESS;
}

int destroy_buf (BUFFER *bd)
{
	free((bd));
	return BUF_SUCCESS;
}
