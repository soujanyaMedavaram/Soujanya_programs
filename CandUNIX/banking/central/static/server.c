# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "ipc.h"
# include "../request_reply.h"
# include "../../sb.h"
# include "config.h"

IPC *ipc_id;
int fd_db;

void catch ( ) {
	remove_ipc ( ipc_id, max_channel ( ), fd_db );
	exit ( 0 );
}

main ( ) {
	FILE *fp;
	Request req;
	Account acc;
	reply reply;

	fp = fopen ( "ser_pid", "r" );
	if (fp != NULL )
		do_exit ( 6, "server already started\n" );
	if ( access ( datafile, F_OK )  ) 
		fd_db = open ( datafile, O_RDWR | O_CREAT , 0600);
	else 
		fd_db = open ( datafile, O_RDWR ); 
	if ( fd_db == -1 ) 
		do_exit ( 2, "fail to open database file\n" );
	switch ( fork ( ) ) {
		case -1 :
			do_exit ( 1, "fork failed\n" );
		case 0:	break;
		default : exit ( 0 );
	}
	fp = fopen( "ser_pid", "w" );
	if ( fp == NULL )
		do_exit ( 2, "Can not open ser_pid\n" );
	fclose ( fp );
//	close ( 0 ); close ( 1 ); close ( 2 );
	ipc_id = create_ipc ( max_channel ( ) );
	if ( ipc_id == NULL )
		fprintf ( stderr, "create_ipc failed\n" );
	signal ( SIGUSR1, catch );
	while ( 1 ) {
		read_request ( ipc_id, &req, sizeof ( req ) ) ;
		switch ( req.type ) {
			case CREATE :
				if ( req.amount < 0 ) {
					reply.result = 0;
					strcpy ( reply.msg, "insufficient balance\n" );
					write_reply ( ipc_id, &reply , sizeof ( reply ), req.rep_chl);
					break;
				}
				strcpy ( acc.name, req.cust_name );
				strcpy ( acc.phone, req.phone );
				acc.balance = req.amount ;
				acc.acc_no = lseek ( fd_db, 0, SEEK_END ) / sizeof ( acc ); 
				acc.acc_no++;
				write ( fd_db, &acc, sizeof ( acc ) );
				reply.result = 1;
				reply.acc_no = acc.acc_no;
				write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl);
				break;
			case DEPOSIT :
				lseek ( fd_db, (req.acc_no -1) * sizeof ( acc ), SEEK_SET );
				read ( fd_db, &acc, sizeof ( acc ) );
				if ( req.acc_no != acc.acc_no ) {
					reply.result = 0;
					strcpy ( reply.msg, "no user with this account number" );
					write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl );
					break;
				}
				acc.balance += req.amount;
				sleep ( 5 );
				lseek ( fd_db, (req.acc_no -1 ) * sizeof ( acc ), SEEK_SET );
				write ( fd_db, &acc, sizeof ( acc ) );
				reply.result = 1;
				write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl );
				break;
			case WITHDRAW :
				lseek ( fd_db, (req.acc_no -1) * sizeof ( acc ), SEEK_SET );
				read ( fd_db, &acc, sizeof ( acc ) );
				if ( req.acc_no != acc.acc_no ) {
					reply.result = 0;
					strcpy ( reply.msg, "no user with this account number" );
					write_reply ( ipc_id, &reply, sizeof ( reply ) , req.rep_chl);
					break;
				}
				if ( acc.balance < req.amount ) {
					reply.result = 0;
					strcpy ( reply.msg, "insufficient balance\n" );
					write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl);
					break;
				}
				acc.balance -= req.amount;
				sleep ( 5 );
				lseek ( fd_db, (req.acc_no -1 ) * sizeof ( acc ), SEEK_SET );
				write ( fd_db, &acc, sizeof ( acc ) );
				reply.result = 1;
				write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl);
				break;
			case CHANGE:
				lseek ( fd_db, (req.acc_no -1) * sizeof ( acc ), SEEK_SET );
				read ( fd_db, &acc, sizeof ( acc ) );
				if ( req.acc_no != acc.acc_no ) {
					reply.result = 0;
					strcpy ( reply.msg, "no user with this account number" );
					write_reply ( ipc_id, &reply, sizeof ( reply ) , req.rep_chl);
					break;
				}
				strcpy ( acc.phone, req.phone );
				sleep ( 5 );
				lseek ( fd_db, (req.acc_no -1 ) * sizeof ( acc ), SEEK_SET );
				write ( fd_db, &acc, sizeof ( acc ) );
				reply.result = 1;
				strcpy ( reply.phone, acc.phone );
				write_reply ( ipc_id, &reply, sizeof( reply), req.rep_chl );
				break;
			case BALANCE :
				lseek ( fd_db, (req.acc_no - 1) * sizeof ( acc ), SEEK_SET );
				read ( fd_db, &acc, sizeof ( acc ) );
				if ( req.acc_no != acc.acc_no ) {
					reply.result = 0;
					strcpy ( reply.msg, "no user with this account number\n" );
					write_reply ( ipc_id, &reply, sizeof ( reply ) , req.rep_chl);
					break;
				}
				reply.result = 1;
				reply.amount = acc.balance;
				write_reply ( ipc_id, &reply, sizeof ( reply ), req.rep_chl) ;
				break;
		}
	}
}
	
