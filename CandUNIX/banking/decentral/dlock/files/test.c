# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../sb.h"

main ( ) {
	int fd ;
	Account acc1;
	fd = open ( "info.data", O_RDONLY );
	if ( fd < 0 )
		printf ( "open failed\n" );
	while ( read ( fd, &acc1, sizeof ( acc1 ) ))
	printf ( "%d %s %s %d\n", acc1.acc_no, acc1.name, acc1.phone, acc1.balance );
	/*read ( fd, &acc1.acc_no, sizeof ( acc1.acc_no ) );
	read ( fd, &acc1.name, sizeof ( acc1.name) );
	read ( fd, &acc1.phone, sizeof ( acc1.phone) );
	read ( fd, &acc1.balance, sizeof ( acc1.balance ) );*/
	return 0;
}

