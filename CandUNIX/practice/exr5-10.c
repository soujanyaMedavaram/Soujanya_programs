# include <stdio.h>
# include <stdlib.h>

int arr[25] , i = 0;
void push ( int val )
{
	arr[i++] = val;
}
int pop() {
	return arr[--i];
}

main ( int argc, char *argv[] ) {
	int opr2;
	if (argc == 1) {
		fprintf ( stderr, "Usage: expression\n" );
		exit ( 1 );
	}
	while (*++argv) 
		if (isdigit(**argv))
			push(atoi(*argv));
		else if (**argv == '+')
			push ( pop() + pop());
		else if (**argv == '-') {
			opr2 = pop();
			push ( pop() - opr2 );
		}
		else if (**argv == '*')
			push ( pop() * pop() );
		else if (**argv == '/') {
			opr2 = pop();
			if (opr2 != 0)
				push ( pop() / opr2);
			else printf ( "\nZEroerror division\n");
		}
		else {
			printf ( "\n invalid argument\n" );
			exit ( 1 );
		}
		printf ("\n the expr value is %d\n", pop() );
}
