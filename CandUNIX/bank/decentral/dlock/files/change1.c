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
	struct flock lock;

	if ( argc != 3 )
		do_exit ( 1, "Usage: change <acc_no> <phone_no>\n" );
	fd = open ( "info.data", O_RDWR );
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_len = sizeof ( acc );
	lock.l_pid = getpid ( );
//	flock ( fd, LOCK_EX );
	acc_no = atoi ( argv[1] );
	if ( fd < 0 )
		do_exit( 2, "data base file can not be opened\n" );
	lock.l_start = lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	//flock ( fd, LOCK_EX ); 
	if ( fcntl ( fd, F_SETLKW, &lock ) == -1 )
		do_exit ( 3, " signal received . abort\n" );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "no user with tihs account number\n" );
	strcpy ( acc.phone , argv[2] );
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
//	flock ( fd, LOCK_UN );
	fcntl ( fd, F_SETLK , &lock );
	close ( fd );
	return 0;
}

