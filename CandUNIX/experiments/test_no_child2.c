# include <stdio.h>

main ( ) {
	int count ;
	int chl_ret;

	count = 0;
	while ( (chl_ret = fork ( )) ) {
		if ( chl_ret == 0 )  
			exit ( 0 ) ;
		else count++;
	}
	if ( chl_ret == -1 )
	printf ( " count = %d\n", count );
}
