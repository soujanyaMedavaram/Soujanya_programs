# include <stdio.h>
# include "../../request.h"
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>

# define REQ_FIFO 	"req_fifo"

int fd_write;
char *rep_fifo;

void create ( char *name, char *phone, int amount ) ;
void deposit ( int acc_no, int amount ) ;
void withdraw ( int acc_no, int amount ) ;
void change ( int acc_no, char *phone ) ;
void balance ( int acc_no ) ;

void catch ( ) { 
	unlink ( REQ_FIFO );
	unlink ( rep_fifo );
}

main  ( ) {
	int fd_read;
	int acc_no, amount;
	Request req;
	int cr_flag, dp_flag, wd_flag, ch_flag, bl_flag;
	FILE *fp;

	if ( mkfifo ( REQ_FIFO, 0600 ) < 0 && EEXIST != errno )
		do_exit ( 1, "fail to create request fifo\n" );
	signal ( SIGUSR1, catch );
	switch ( fork ( ) ) {
		case -1:
			do_exit ( 2, "fork failed\n" );
		case 0: break;
		default : exit ( 0 );
	}
	fp = fopen ( "ser_pid", "w" );
	if ( fp == NULL )
		do_exit ( 3, "No write permission in current directory\n" );
	fprintf ( fp, "%d", getpid ( ) );
	fclose ( fp );	
	while ( 1 ) {
		cr_flag = dp_flag = wd_flag = ch_flag = bl_flag = 1;
		fd_read = open ( REQ_FIFO, O_RDONLY );
		if ( fd_read < 0 )
			do_exit ( 2, "read permission denied for request fifo \
			in current directory\n" ); 
		read ( fd_read, &req, sizeof ( req ) );
		if ( mkfifo ( req.rep_name, 0600 ) < 0 && EEXIST != errno )
			do_exit ( 3, "reply fifo creation failed\n" );
		cr_flag = strcmp ( req.cmd_name, "create" );
		dp_flag = strcmp ( req.cmd_name, "deposit" );
		wd_flag = strcmp ( req.cmd_name, "withdraw" );
		ch_flag = strcmp ( req.cmd_name, "deposit" );
		bl_flag = strcmp ( req.cmd_name, "balance" );
		acc_no = atoi ( req.arg_accno );
		amount = atoi ( req.amount );
		if ( !cr_flag )
			create ( req.cust_name, req.phone_num, amount );
		else if ( !dp_flag )
			deposit ( acc_no, amount );
		else if ( !wd_flag )
			withdraw ( acc_no, amount );
		else if ( !ch_flag )
			change ( acc_no, req.phone_num );
		else if ( !bl_flag )
			balance ( acc_no );
		fd_write = open ( req.rep_name, O_WRONLY );
		if ( fd_write < 0 )
			do_exit ( 4, "write permission denied to write fifo\n" );
		write ( fd_write, "transaction completed\n" , 100);
		close ( fd_write );
	}
}

void create ( char *name, char *phone, int amount ) {
	int fd;
	Account acc;

	if ( access ( datafile, F_OK )  ) 
		fd = open ( datafile, O_WRONLY | O_CREAT ,0600);
	else 
		fd = open ( datafile, O_APPEND | O_WRONLY ); 
	if ( fd == -1 ) 
		write ( fd_write,  "fail to open the fail\n" , 100);
	acc.acc_no = lseek ( fd, 0, SEEK_END ) / 76; //76-> sizeof record 
	acc.acc_no++;
	sleep ( 5 );
	strcpy ( acc.name, name );
	strcpy ( acc.phone, phone );
	acc.balance = amount;
	if ( acc.balance < 0 )
		write ( fd_write, "invalid balance (balance >= 0 )\n" , 100 );
	write ( fd, &acc, sizeof ( acc ) );
	close ( fd );
}

void deposit ( int acc_no, int amount ) {
	int fd;
	Account acc;
	
	fd = open ( datafile, O_RDWR );
	if ( fd < 0 )
		write ( fd_write, "database file can not be opened\n" , 100 );
	lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		write ( fd_write, "no user with tihs account number\n", 100 );
	acc.balance += amount;
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
	close ( fd );
}

void withdraw ( int acc_no, int amount ) {
	int fd;
	Account acc;
	
	fd = open ( datafile, O_RDWR );
	if ( fd < 0 )
		write ( fd_write, "database file can not be opened\n" , 100 );
	lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		write ( fd_write, "no user with tihs account number\n", 100 );
	if ( acc.balance < amount )
		write ( fd_write, "insufficient balance\n" , 100 );
	acc.balance -= amount;
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
	close ( fd );
}

void change ( int acc_no, char *phone ) {
	int fd ;
	Account acc;

	fd = open ( "info.data", O_RDWR );
	if ( fd < 0 )
		write ( fd_write, "data base file can not be opened\n", 100 );
	lseek ( fd, (acc_no -1) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		do_exit ( 2, "no user with tihs account number\n" );
	strcpy ( acc.phone , phone );
	sleep ( 5 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	write ( fd, &acc, sizeof ( acc ) );
}

void balance ( int acc_no ) {
	int fd ;
	Account acc;

	fd = open ( "info.data", O_RDONLY );
	if ( fd < 0 )
		write ( fd_write, "data base file can not be opened\n", 100 );
	lseek ( fd, (acc_no -1 ) * sizeof ( acc ), SEEK_SET );
	read ( fd, &acc, sizeof ( acc ) );
	if ( acc_no != acc.acc_no )
		write ( fd_write, "No user with account no \n" , 100 );
	printf ( "%d %s %s %d\n", acc.acc_no, acc.name, acc.phone, acc.balance );
	close ( fd );
}
