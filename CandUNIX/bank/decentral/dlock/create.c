# include <stdio.h>
# include <sys/file.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "../../sb.h"
# include <unistd.h>

	
main ( int argc, char **argv ) {
	int fd;
	Account acc;
	struct flock lock;

	if ( argc != 4 ) 
		do_exit ( 1, "Usage: create <name> <phone_no> <balance>=0>\n" ); 
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_len = sizeof ( acc );
	lock.l_pid = getpid ( );
	if ( access ( datafile, F_OK )  ) 
		fd = open ( datafile, O_WRONLY | O_CREAT ,0600);
	else 
		fd = open ( datafile, O_APPEND | O_WRONLY ); 
	if ( fd == -1 ) 
		do_exit ( 2,  "fail to open the fail\n" );
	//flock ( fd, LOCK_EX );
	lock.l_start = lseek ( fd, 0, SEEK_END );
	fcntl ( fd, F_SETLKW, &lock );
	acc.acc_no = lseek ( fd, 0, SEEK_END ) / 76; //76-> sizeof record 
	acc.acc_no++;
	strcpy ( acc.name, argv[1] );
	strcpy ( acc.phone, argv[2] );
	acc.balance = atoi ( argv[3] );
	if ( acc.balance < 0 )
		do_exit ( 3, "invalid balance (balance >= 0 )\n" );
	write ( fd, &acc, sizeof ( acc ) );
	//flock ( fd, LOCK_UN );
	fcntl ( fd, F_SETLK, &lock );	
	close ( fd );
}
