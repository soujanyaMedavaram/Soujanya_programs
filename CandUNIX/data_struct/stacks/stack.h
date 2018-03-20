// stack.h : an interface 

typedef struct stack STACK;

STACK *stack_open (int nitems, int size);
int push (STACK *sd, char *item);
int pop (STACK *sd, char *item);
void close_stack (STACK *sd);
int stack_full  (STACK *sd);
int stack_empty (STACK *sd);
int stack_transient (STACK *sd);

#define S_SUCCESS	0
#define S_FAIL		NULL
#define S_FULL		-1
#define S_EMPTY		-2
