# include <stdio.h>

main  ( ) {
	FILE *fp;
	char c;
	fp = fopen ( "student", "r" );
	printf ( "--------------------------------------------------\n" );
	printf ( "| Name   RollNo.   | Marks obtained\n" );
	printf ( "|                  | --------------------------------\n" );
	printf ( "|                  | physics | chemistry | Maths\n" );
	printf ( "|----------------------------------------------------\n" );
	while ( ( c= getc(fp )) != EOF ) 
		putchar ( c );
}

