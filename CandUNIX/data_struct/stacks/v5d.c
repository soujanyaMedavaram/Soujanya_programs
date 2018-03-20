#include<stdio.h>

#define LENGTH 50
#define ROQ	5 

int *stack;
int sp;
char line[LENGTH], *p;

main(){
	sp = 0;
	if (!(stack = (int *)malloc(ROQ * sizeof(stack)))){
		printf("\n memory can not be allocated\n");
		exit(1);
	}
	int m = 1;
	while (1){
		if (!sp)
			printf( "<num> to push; e to exit:");
		else
			printf( "<num> to push; p to pop; e to exit:");
		if( !fgets( line, LENGTH, stdin))
			exit(1);
		for ( p = line; *p == ' ' || *p == '\t'; p++);
		switch( *p ){
			default: continue;
			case '\n': continue;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':
					stack[sp++] = atoi(p);
					if (!(sp % ROQ)){
					   printf("%d - memory\n",sp%ROQ);
					   stack = (int *)realloc(stack, ++m * ROQ * sizeof(stack));
					}
				continue;

			case 'p': case 'P':
				if (!sp) ;
				else
					printf( "%d\n", stack[--sp]);
				continue;
			case 'e': case 'E':
				if (sp){
					printf("you forgot to pop\n");
					while (sp)
						printf("%d\n", stack[--sp]);
				}
				printf( "bye bye\n");
				exit(0);
		}
	}
}
		
