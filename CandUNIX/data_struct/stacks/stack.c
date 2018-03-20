#include<stdio.h>
#include "stack.h"
struct stack
{
	char *beg;
	char *sp;
	char *end;
	int n;
	int size;
};

char *malloc(int);
int free(char *);

STACK * stack_open(int n, int size)
{
	register STACK *sd;
	int x;
	if (n < 1 || size < 1) return S_FAIL;
	x = sizeof(*sd);
	sd = (STACK *)malloc(sizeof(*sd));
	if (sd == NULL) return S_FAIL;
	sd->beg = malloc(n * size);
	sd->sp = sd->beg;
	sd->end = sd->beg + n * size;
	sd->n = n;
	sd->size = size;
	return sd;
}

int push (register STACK *sd, char *item)
{
	if ( stack_full (sd)) return S_FULL;
	memcpy (sd->sp, item, sd->size);
	sd->sp += sd->size;
	return S_SUCCESS;
}

int pop (register STACK *sd, char *item)
{
	if(stack_empty(sd)) return S_EMPTY;
	sd->sp -= sd->size;
	memcpy (item, sd->sp, sd->size);
	return S_SUCCESS;
}

void close_stack(STACK *sd)
{
	free(sd->beg);
	free((char *)sd);
}

int stack_full (STACK *sd) {
	return sd->sp == sd->end;
}

int stack_empty (STACK *sd) {
	return sd->sp == sd->beg;
}

int stack_transient (STACK *sd) {
	return 1;
}
