# include <stdio.h>
# include <sys/file.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../sb.h"

main ( int argc, char **argv ) {
	int acc_no, amt, fd, nrec, flag;
	Account acc;
	struct flock lock;

	if ( !strcmp (argv[0], "withdraw") )
		flag = CMD_WITHDRAW;
	else if ( !strcmp (argv[0], "deposit") )
		flag = CMD_DEPOSIT;
	else if ( !strcmp (argv[0], "balance") )
		flag = CMD_BALANCE;
	else if ( !strcmp (argv[0], "change") )
		flag = CMD_CHANGE;
	else flag = CMD_ERROR;
	if ( flag == CMD_ERROR )
		do_exit ( 1, "Command error\n" );
	if ( flag == CMD_BALANCE && argc != 2 || flag != CMD_BALANCE && argc != 3 )
		do_exit ( 2, "Usage: withdraw <acc_no> <amount>\n"
					 "       deposit  <acc_no> <amount>\n"
					 "       balance  <acc_no>\n"
					 "       change   <acc_no> <phone_no>\n" );
	fd = open ( datafile , O_RDWR );
	if ( fd < 0 )
		do_exit ( 3, "Database file cannot be accessed\n" );
	acc_no = atoi ( argv[1] );
	nrec = lseek ( fd, 0, 2 ) / sizeof (acc);
	if ( acc_no > nrec || acc_no < 1 )
		do_exit ( 4, "Specify existing record number\n" );
	lock.l_start = lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	if ( flag != CMD_BALANCE ) {
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_len = sizeof ( acc );
		lock.l_pid = getpid ( );
		//flock ( fd, LOCK_EX );
		if ( fcntl ( fd, F_SETLKW, &lock ) == -1 )
			do_exit ( 4, "Signal recd.  abort\n" );
	}
	read ( fd, &acc, sizeof( acc ) );
	sleep ( 5 );
	if ( flag == CMD_WITHDRAW ) {
		amt = atoi ( argv[2] );
		if ( amt < 0 )
			do_exit ( 5, "amount must be positive\n" );
		if ( (acc.balance -= amt) < 0 )
			do_exit ( 5, "balance insufficient\n" );
	} else if ( flag == CMD_DEPOSIT ) {
		amt = atoi ( argv[2] );
		if ( amt < 0 )
			do_exit ( 5, "amount must be positive\n" );
		acc.balance += amt;
	} else if ( flag == CMD_CHANGE )
		strcpy ( acc.phone, argv[2] );
	if ( flag != CMD_BALANCE ) {
		lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
		write ( fd, &acc, sizeof ( acc ) );
		// No need to unlock since close will do it
			//flock ( fd, LOCK_UN );
			lock.l_type = F_UNLCK;
			fcntl ( fd, F_SETLK, &lock );
	}
	if ( flag != CMD_CHANGE )
		printf ( "Acc %d   %s  Closing Balance %d\n",
				acc.acc_no, acc.name, acc.balance );
	close ( fd );
}
