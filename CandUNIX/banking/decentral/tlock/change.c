# include <stdio.h>
# include <sys/file.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../sb.h"

main (int argc, char *argv[] ) {
	int fd , acc_no;
	Account acc;

	if ( argc != 3 )
		do_exit ( 1, "Usage: change <acc_no> <phone_no>\n" );
	sem_lock ( 0 );
	fd = open ( "info.data", O_RDWR );
	acc_no = atoi ( argv[1] );
	if ( fd < 0 )
		do_exit( 2, "data base file can not be opened\n" );
	lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "no user with tihs account number\n" );
	strcpy ( acc.phone , argv[2] );
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
	sem_lock ( 1 );
	close ( fd );
	return 0;
}

