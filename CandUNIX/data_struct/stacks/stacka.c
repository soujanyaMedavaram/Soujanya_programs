#include<stdio.h>
#include "stack.h"

char *malloc(int);
int free(char *);

#define ROQ 10

struct stack
{
	char *beg;
	char *sp;
	char *end;
	int n;
	int size;
};


STACK * stack_open(int nitems, int size)
{
	register STACK *sd;

	sd = (STACK *)malloc(sizeof(*sd));
	if (sd == NULL) return S_FAIL;
	sd->beg = malloc(ROQ * size);
	sd->sp = sd->beg;
	sd->end = sd->beg + ROQ * size;
	sd->n = ROQ;
	sd->size = size;
	return sd;
}

int push (register STACK *sd, char *item)
{
	static int mem_count = 1;
	static int x = 1;
	if (!(x % ROQ))
	{
//		printf("\n mem_count %d and n %ROQ is %d\n",mem_count,x%ROQ);
		sd->beg = (char *)realloc(sd->beg,mem_count++ * ROQ * sd->size);
		sd->end = sd->beg + mem_count * ROQ * sizeof(*sd);
		sd->n = mem_count * ROQ;
	}
	memcpy (sd->sp, item, sd->size);
	sd->sp += sd->size;
	x++;
	return S_SUCCESS;
}

int pop (register STACK *sd, char *item)
{
	if(stack_empty(sd)) return S_EMPTY;
	sd->sp -= sd->size;
	memcpy (item, sd->sp, sd->size);
	return S_SUCCESS;
}

int close_stack(STACK *sd)
{
	free(sd->beg);
	free((char *)sd);
	return S_SUCCESS;
}

int stack_full (STACK *sd) {
	return 0;
}

int stack_empty (STACK *sd) {
	return sd->sp == sd->beg;
}
