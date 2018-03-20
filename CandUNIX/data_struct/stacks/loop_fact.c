# include <stdio.h>
# include "stack.h"

# define PUSH	1
# define POP	0

struct s_fact {
	int num;
	char action;
};

main  ( ) {
	int num, val ;
	struct s_fact s_fact;
	STACK *sd;

	printf ( "\n enter a number\n" );
	scanf ( "%d", &num );
	val = 1;
	sd = stack_open( 50, sizeof ( s_fact ) );
	s_fact.num = num;
	s_fact.action = PUSH;
	push ( sd, (char *) &s_fact );
	while ( 1 )  {
		if ( pop ( sd, (char *)&s_fact) == S_EMPTY )
			break;
		if ( s_fact.action == PUSH ) {
			s_fact.action = POP;
			push ( sd, ( char *) &s_fact );
			--num;
			if ( num > 0 ) {
				s_fact.num = num;
				s_fact.action = PUSH;
				push ( sd, (char *)&s_fact );
			}
		}
		else  val = val * s_fact.num;
	}
	printf ( " factorial = %d\n", val );
}
		
