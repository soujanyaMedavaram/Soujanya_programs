# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "stack.h"

char line[100];

main ( ) {
	register STACK **sd = NULL;
	register char *p;
	int num, stack_num, j;
	static i = 0;

	while ( 1 ) {
		printf ("\nC to create stack;s<num> to select;p to pop; num to push	e to exit\n");
		fgets ( line, 100, stdin );
		for ( p = line; *p == ' ' || *p == '\t'; p++ );
		switch(*p) {
			case 'c': case 'C':
				sd = realloc ( sd, (i+2) * sizeof (STACK *) );
				sd[++i] = ( STACK *) stack_open ( i,sizeof(num) );
				break;
			case 's': case 'S':
				p++;
				stack_num = atoi(p);
				if ( stack_num > i || stack_num < 1 )
					printf ( "\n no stack with the number\n" );
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				num = atoi(p);
				push(sd[stack_num], (char *)&num);	
				break;
			case 'p': case 'P':
				if ( stack_empty ( sd[stack_num] ) ) {
					printf ("\n stack is empty \n");
					break;
				}
				pop(sd[stack_num], (char *)&num );
				printf ("%d\n",num);
				break;
			case 'e': case 'E':
				for ( j = 1; j <= i; j++) {
					printf ( "\n s%d\n",j);
					while ( !stack_empty ( sd[j] ) ) {
						pop(sd[j], (char *)&num);
						printf ("%d\n",num);
					}
					close_stack ( sd[j] );
				}
				exit ( 0 );
		}
	}
}

