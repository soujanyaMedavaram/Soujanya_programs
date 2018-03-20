# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include "../sb.h"

main ( ) {
	int fd ;
	Account acc1;
	fd = open ( "info.data", O_RDONLY );
	if ( fd < 0 ) {
		fprintf ( stderr , "fail to open inof.data\n" );
		exit ( 1 );
	}
	while ( read ( fd, &acc1, sizeof ( acc1 ) ))
	printf ( "%d %s %s %d\n", acc1.acc_no, acc1.name, acc1.phone, acc1.balance );
	return 0;
}

