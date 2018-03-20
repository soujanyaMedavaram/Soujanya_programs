# include <stdio.h>

main ( ) {
	int count = 0, break_flag = 0;
	while (  1 ) {
		switch ( fork  ( )  ) {
			case -1 : fprintf ( stderr, "fork failed\n" );
				printf ( "No of childs = %d\n", count );
				break_flag  = 1;
				count = 0;
				continue;
			case 0:
				//break;
				exit ( 0 );
		}
		if ( break_flag == 1 ) break;
		count++;
		//wait ( NULL );
	}
}
