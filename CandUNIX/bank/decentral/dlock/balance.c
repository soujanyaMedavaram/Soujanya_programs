# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../sb.h"

main (int argc, char *argv[] ) {
	int fd , acc_no;
	Account acc;

	if ( argc != 2 )
		do_exit ( 1, "Usage: balance <acc_no> \n" );
	fd = open ( "info.data", O_RDONLY );
	acc_no = atoi ( argv[1] );
	if ( fd < 0 )
		printf ( "open failed\n" );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "No user with account no \n" );
	printf ( "%d %s %s %d\n", acc.acc_no, acc.name, acc.phone, acc.balance );
	close ( fd );
	return 0;
}

