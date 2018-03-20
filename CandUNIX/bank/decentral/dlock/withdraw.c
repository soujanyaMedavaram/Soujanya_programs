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
	struct flock lock;
	
	if ( argc != 3 )
		do_exit ( 1, "Usage: deposit <acc_no> <amount>\n" );
	acc_no = atoi ( argv[1] );
	amt = atoi ( argv[2] );
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_len = sizeof ( acc );
	lock.l_pid = getpid ( );
	fd = open ( datafile, O_RDWR );
	if ( fd < 0 )
		do_exit ( 2, "database file can not be opened\n" );
	lock.l_start = lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	//flock ( fd, LOCK_EX ); 
	if ( fcntl ( fd, F_SETLKW, &lock ) == -1 )
		do_exit ( 3, " signal received . abort\n" );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "no user with tihs account number\n" );
	if ( acc.balance < amt ) 
		do_exit ( 2, " Insuffient balance\n" );
	acc.balance -= amt;
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
//	flock ( fd, LOCK_EX );
	fcntl ( fd, F_SETLK , &lock );
	close ( fd );
}

