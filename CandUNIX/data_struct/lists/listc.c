# include <stdio.h>
# include "listc.h"
# define L_MAGIC (((long) 'L' << 24) | ((long) 'l' << 16) | \
							((long) 'S' << 8) | ((long) 'T'))
char *malloc(int);
//int free(char *);
LIST *open_list (int size)
{
	register LIST *ld;

	if (size < 1) return L_FAIL;
	ld = (LIST *)malloc(sizeof(LIST));
	First = NULL;
	Last = NULL;
	Transferred = NULL;
	Nitems = 0;
	Ntrans = 0;
	Size = size;
	Magic = L_MAGIC;
	Transfer_flag = 0;
	return ld;
}

int close_list (register LIST *ld)
{
	register struct item *item;
	register struct item *p;

	if (Magic != L_MAGIC) return L_ILLEGAL;
	
	for (item = First; item;)
	{
		p = item;
		free (p);
		item = p->next;
	}
	free(ld);
	return L_SUCCESS;
}

int append(register LIST *ld, char *data)
{
	register struct item *item;

	if (Magic != L_MAGIC) return L_ILLEGAL;
	item = (struct item *)malloc(sizeof(*item) + Size - 1);
	Ntrans++;
	Nitems++;
	Next = NULL;
	Prev = Last;
	memcpy (Data,data,Size);
	if (Last) Last->next = item;
	else First = item;
	Last = item;
	return L_SUCCESS;
}

int read_first(register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = First;
	memcpy(data,Transferred->data,Size);
	Ntrans++;
	Dir = FORWARD;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_last(register LIST *ld, char *data)
{
	if(Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = Last;
	memcpy(data,Transferred->data,Size);
	Ntrans++;
	Dir = REVERSE;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_next(register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	if (!Transferred) Transferred = First;
	else if(Dir == REVERSE);
	else if (!Transferred->next) return L_NO_MORE;
	else Transferred = Transferred->next;
	memcpy (data,Transferred->data,Size);
	Ntrans++;
	Dir = FORWARD;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_prev (register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	if (!Transferred) Transferred = Last;
	else if (Dir == FORWARD);
	else if (!Transferred->prev) return L_NO_MORE;
	else Transferred = Transferred->prev;
	memcpy (data, Transferred->data,Size);
	Ntrans++;
	Dir = REVERSE;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int delete(register LIST *ld)
{
	register struct item *item;
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Transfer_flag) return L_NOT_READ;
	item = Transferred;
	if (item == First) First = Next;
	if (item == Last) Last = Prev;
	if (Prev) Prev->next = Next;
	if (Next) Next->prev = Prev;
	if (Dir == FORWARD)
		Transferred = Prev;
	else Transferred = Next;
	free (item);
	Nitems--;
	Ntrans++;
	Transfer_flag = 0;
	return L_SUCCESS;
}

long tot_cal(register LIST *ld)
{
	long total = 0;
	char *data;
	Temp = First;
    while (Temp != NULL)	
	{
		total += *(Temp->data);
		Temp = Temp->next;
	}
	return total;
}

double avg_cal (register LIST *ld)
{
	double avg;
	avg = tot_cal(ld);
	printf("the total in avg is %lf:",avg);
	printf("the no of items is %ld",Nitems);
	avg = avg /(double) Nitems;
	return avg;
}

void min_max(register LIST *ld)
{
	Temp= First;
	int num;
	int min = atoi(First->data);
	int max = atoi(First->data);
	while (Temp->next != NULL)
	{
		num = atoi(Temp->data);
		if (num > max)
			max = num;
		if (num < min)
			min = num;
		Temp = Temp->next;
	}
	printf("\nMaximum is %d\n",max);
	printf("\nMinimum is %d\n",min);
}

long stats_cal(register LIST *ld)
{
	return Ntrans;
}
