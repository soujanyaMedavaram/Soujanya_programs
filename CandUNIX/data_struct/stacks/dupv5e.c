#include<stdio.h>

#define LENGTH 50
#define ROQ 4

int *stack;
int sp, i;
char line[LENGTH], *p;

main()
{
	sp = ROQ;
	int m = 1;
	stack = (int *)malloc(ROQ * sizeof(stack));
	while (1)
	{
		printf( "<num> to push; p to pop; e to exit:");
		if( !fgets( line, LENGTH, stdin))
			exit(1);
		for ( p = line; *p == ' ' || *p == '\t'; p++);
		switch( *p )
		{
			default: continue;
			case '\n': continue;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':
					stack[sp--] = atoi(p);
					printf ("\n sp = %d\n",sp);
					if ( sp == 0 ){
						stack = (int *)realloc(stack,++m * ROQ * sizeof(stack));						if (stack == NULL)
						{
							printf ("memory not allocated\n");
							exit(2);
						}
						sp = m * ROQ;
						i = (m - 1) * ROQ;
							while( i > 0)
						stack[sp--] = stack[i--];
					}
					continue;

			case 'p': case 'P':
				if (sp == (m * ROQ)) 
					printf ("\n Stack is empty\n");
				else
					printf( "%d\n", stack[++sp]);
				continue;
			case 'e': case 'E':
				if (sp != (m * ROQ))
				{
					printf("you forgot to pop\n");
					while (sp != (m * ROQ))
						printf("%d\n", stack[++sp]);
				}
				printf( "bye bye\n");
				exit(0);
		}
	}
}
		
