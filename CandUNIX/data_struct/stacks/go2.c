# include <stdio.h>

main ( ) {
	
	int i = 0;
	hai :
		printf ( "hai \n" );
	while ( i < 5 ) {
		i++;
		goto hai;
	}
	exit ( 0 );
}

