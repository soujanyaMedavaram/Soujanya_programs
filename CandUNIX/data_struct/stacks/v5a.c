#include<stdio.h>

#define LENGTH 50
#define NMAX 20

int stack[NMAX];
int sp;
char line[LENGTH], *p;

main()
{
	sp = -1;
	while (1)
	{
		if (sp == NMAX)
			printf( "p to pop; e to Exit:");
		else if (sp == -1)
			printf( "<num> to push; e to exit:");
		else
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
				if (sp == NMAX)
					printf( "stack over flow\n");
				else
					stack[++sp] = atoi(p);
				continue;

			case 'p': case 'P':
				if (sp == -1) ;
				else
					printf( "%d\n", stack[sp--]);
				continue;
			case 'e': case 'E':
				if (sp != -1)
				{
					printf("you forgot to pop\n");
					while (sp != -1)
						printf("%d\n", stack[sp--]);
				}
				printf( "bye bye\n");
				exit(0);
		}
	}
}
		
