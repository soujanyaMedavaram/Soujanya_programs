# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../../utils.h"
# include "../sb.h"
# include "ipc.h"
# include "proto.h"
# include "selection.h"


int main ( ) {
	IPC * ipc_id;
	Request request;
	Account acc;
	Reply reply;
	int fd_db, client_chan, max_chan, i, *occupied, write_flag;
	int shutdown_flag;

	if ( access ( datafile, F_OK )  ) 
		 fd_db = open ( datafile, O_RDWR | O_CREAT , 0600);
	else fd_db = open ( datafile, O_RDWR ); 
	if ( fd_db == -1 ) 
		do_exit ( 2, "Cannot open database file." );
	switch ( fork ( ) ) {
		case -1 : do_exit ( 3, "Cannot fork." );
		case 0  : break;
		default : exit ( 0 );
	}
	ipc_id = create_ipc ( max_chan = max_channel ( ), sizeof (Request) );
	if ( dynamic_selection () ) {
		occupied = calloc ( ++max_chan, sizeof( int ) );
		occupied[0]= 1;	// Never used
		occupied[1] = 1;	// Request channel
		occupied[2] = 1;	// Channel No. reply channel
	}
	if ( ipc_id == NULL      && fprintf ( stderr, "Cannot create IPC\n" ) ||
		 ipc_id == (IPC *) 1 && fprintf ( stderr, "Server already started\n" ) )
		exit ( 1 );

//	close ( 0 ); close ( 1 ); close ( 2 );
	shutdown_flag = 0;
	while ( 1 ) {
		client_chan = receive_ipc ( ipc_id, & request ) ;
		write_flag = reply.result = 1;
		if ( request.type == CMD_DEPOSIT || request.type == CMD_WITHDRAW ||
			 request.type == CMD_CHANGE  || request.type == CMD_BALANCE ) {
			lseek ( fd_db, (request.acc_no -1) * sizeof ( acc ), SEEK_SET );
			read ( fd_db, & acc, sizeof ( acc ) );
			if ( request.acc_no != acc.acc_no ) {
				reply.result = 0;
				reply.info = 2;
				write_flag = 0;
			}
		}
		if ( reply.result == 1 ) switch ( request.type ) {
			case CMD_CONNECT :
				for ( i = 3; i < max_chan; i++ )
					if ( !occupied[i] ) break;
				if ( i < max_chan ) {
					occupied[i] = 1;
					reply.info = i;
				} else reply.info = -1;
				write_flag = 0;
				break;

			case CMD_CREATE :
				if ( request.amount < 0 ) {
					reply.result = 0;
					reply.info = 1;
				} else {
					strcpy ( acc.name, request.name );
					strcpy ( acc.phone, request.phone );
					acc.balance = request.amount ;
					acc.acc_no = lseek( fd_db, 0, SEEK_END ) / sizeof (acc) + 1;
					reply.info = acc.acc_no;
				}
				break;

			case CMD_DEPOSIT :
				acc.balance += request.amount;
				break;

			case CMD_WITHDRAW :
				if ( acc.balance < request.amount ) {
					reply.result = 0;
					reply.info = 1;
				} else {
					acc.balance -= request.amount;
					sleep ( 5 );
				}
				break;

			case CMD_CHANGE:
				strcpy ( acc.phone, request.phone );
				break;

			case CMD_BALANCE :
				reply.info = acc.balance;
				write_flag = 0;
				break;

			case CMD_QUIT :
				if ( client_chan < 3 || client_chan >= max_chan )
					continue;		// ERROR !!  Don't know what to do
				occupied[client_chan] = 0;
				if ( shutdown_flag == 0 ) continue;
				// NO BREAK

			case CMD_SHUTDOWN :
				shutdown_flag = 1;
				if ( dynamic_selection ( ) ) {
					occupied[client_chan] = 0;
					for ( i = 3; i < max_chan; i++ )
						if ( occupied[i] )
							break;
					if ( i < max_chan ) continue;
				}
				close_ipc ( ipc_id );
				close ( fd_db );
				exit ( 0 );
		}
		if ( write_flag  == 1 ) {
			lseek ( fd_db, (acc.acc_no - 1) * sizeof ( acc ), SEEK_SET );
			write ( fd_db, &acc, sizeof ( acc ) );
		}
		send_ipc ( ipc_id, & reply, sizeof (reply), client_chan );
	}
}
