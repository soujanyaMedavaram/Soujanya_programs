# include <stdio.h>
# define OFFSET(Struct, member)	( (int) & ((Struct *) 0) -> member )

typedef struct hai {
	int a;
	int b;
	double c;
	char str[10];
}Hai;
main ( ) {
	int size;
	Hai h1[2];
	Hai *p, *q;
	p = &h1[0];
	q = &h1[1];
	//printf ( "size = %d\n", p - q );
	size = OFFSET ( Hai, str ); 
	//printf ( " size = %d \n", size );
	printf ( "sizeof = %d \n", sizeof ( Hai ) );
	printf ("\t size of struct is %d \n",(char*)p - (char*) q);
}
