# include <stdio.h>
# include "../../sb.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/file.h>

main ( int argc, char **argv ) {
	int acc_no, amt, fd;
	Account acc;
	
	if ( argc != 3 )
		do_exit ( 1, "Usage: deposit <acc_no> <amount>\n" );
	acc_no = atoi ( argv[1] );
	amt = atoi ( argv[2] );
	sem_lock ( 0 );
	fd = open ( datafile, O_RDWR );
	if ( fd < 0 )
		do_exit ( 2, "database file can not be opened\n" );
	lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "no user with tihs account number\n" );
	if ( acc.balance < amt )
		do_exit ( 3, "insufficient balance\n" );
	acc.balance -= amt;
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
	sem_lock ( 1 );
	close ( fd );
}

