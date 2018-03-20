# define NULL	0
# include "nlist.h"
# define L_MAGIC	1234321

char *malloc(int);
//int free(char *);

LIST *open_list (int size, int (*comp)())
{
	register LIST *ld;
	if ( size < 1 || !comp ) return L_FAIL;
	ld = (LIST *)malloc(sizeof(LIST));
	Biggest = Smallest = Transferred = NULL;
	Nitems = Ntrans = 0;
	Size = size;
	Magic = L_MAGIC;
	Compare = comp;
	Transfer_flag = 0;
	return ld;
}

int close_list (register LIST *ld)
{
	register struct item *item;
	register struct item *p;

	if (Magic != L_MAGIC) return L_ILLEGAL;
	for (item = Smallest; item;)
	{
		p = item;
		free(p);
		item = p->bigger;
	}
	free(ld);
	return L_SUCCESS;
}

int read_smallest(register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = Smallest;
	memcpy (data, Transferred->data,Size);
	Ntrans++;
	Dir = FORWARD;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_biggest (register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	Transferred = Biggest;
	memcpy (data,Transferred->data,Size);
	Ntrans++;
	Dir = REVERSE;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_smaller (register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	if (!Transferred) Transferred = Smallest;
	else if (Dir == REVERSE);
	else if (!Transferred->bigger) return L_NO_MORE;
	else Transferred = Transferred->bigger;
	memcpy (data,Transferred->data,Size);
	Ntrans++;
	Dir = FORWARD;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int read_bigger (register LIST *ld, char *data)
{
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Nitems) return L_EMPTY;
	if (!Transferred) Transferred = Biggest;
	else if (Dir == FORWARD);
	else if (!Transferred->smaller) return L_NO_MORE;
	else Transferred = Transferred->smaller;
	memcpy (data,Transferred->data,Size);
	Ntrans++;
	Dir = REVERSE;
	Transfer_flag = 1;
	return L_SUCCESS;
}

int delete (register LIST *ld)
{
	register struct item *item;
	if (Magic != L_MAGIC) return L_ILLEGAL;
	if (!Transfer_flag) return L_NOT_READ;
	item = Transferred;
	if (item == Smallest) Smallest = Bigger;
	if (item == Biggest) Biggest = Smaller;
	if (Bigger) Bigger->smaller = Smaller;
	if (Smaller) Smaller->bigger = Bigger;
	if (Dir == FORWARD) Transferred = Bigger;
	else Transferred = Smaller;
	free (item);
	Nitems--;
	Ntrans++;
	Transfer_flag = 0;
	return L_SUCCESS;
}

long tot_cal(register LIST *ld)
{
	long total = 0;
	Temp = Smallest;
	while (Temp != NULL)
	{
		total += *(Temp->data);
		Temp = Temp->bigger;
	}
	return total;
}

double avg_cal(register LIST *ld)
{
	double avg = 0;
	avg = tot_cal(ld);
	avg /= Nitems;
	return avg;
}

long stats_cal(register LIST *ld)
{
	Ntrans++;
	return Ntrans;
}

int insert_in_list (register LIST *ld, char *data)
{
	register struct item *item;
	register struct item *p;

	if (Magic != L_MAGIC) return L_ILLEGAL;
	item = (struct item *)malloc(sizeof(*item) + Size -1);
	memcpy (Data,data,Size);
	if (!Nitems)
	{
		Bigger = Smaller = NULL;
		Biggest = Smallest = item;
	}
	else if ((*Compare)(data,Smallest->data) <= 0)
	{
		Bigger = Smallest;
		Smaller = NULL;
		Smallest->smaller = item;
		Smallest = item;
	}
	else if((*Compare)(data,Biggest->data) >= 0)
	{
		Smaller = Biggest;
		Bigger = NULL;
		Biggest->bigger = item;
		Biggest = item;
	}
	else 
	{
		for (p = Smallest->bigger;p;)
			if((*Compare)(data,p->data) <= 0) break;
			else p = p->bigger;
		Bigger = p;
		Smaller = p->smaller;
		p->smaller->bigger = item;
		p->smaller = item;
	}
	Ntrans++;
	Nitems++;
	return L_SUCCESS;
}

