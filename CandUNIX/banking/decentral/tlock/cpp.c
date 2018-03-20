# include <stdio.h>
struct hai {
int a;
};
struct hello {
	int b;
};
void sub1 ( ) {
	printf ( "sub1\n" );
}

void sub2 ( ) {
	printf ( "sub2\n" );
}

main ( ) {
	printf ( "main \n" );
	sub1 ( );
	sub2 ( );
}

