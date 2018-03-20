//	client.c

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../../utils.h"
# include "../sb.h"
# include "ipc.h"
# include "proto.h"
# include "selection.h"

const char * errors[] = {
	"",
	"insufficient balance",
	"no user with this account number",
	NULL
};

const struct {
	char * cmd;
	int request;
	int nargs;
	char * error;
} cmd_list[] = { 
	{ "create",   CMD_CREATE,   4, "create <name> <phone> <balance>" },
	{ "deposit",  CMD_DEPOSIT,  3, "deposit <acc_no> <amount>" },
	{ "withdraw", CMD_WITHDRAW, 3, "withdraw <acc_no> <amount>" },
	{ "change",   CMD_CHANGE,   3, "change <acc_no> <amount>" },
	{ "balance",  CMD_BALANCE,  2, "balance <acc_no>" },
	{ "shutdown", CMD_SHUTDOWN, 1, "shutdown" },
	{ NULL }
};

main ( int argc, char *argv[] ) {
	Request request;
	Reply reply;
	int i, curr_chan;
	FILE * fp;
	IPC  * ipc_id;
	int size;

	curr_chan = curr_channel ( );
	if ( curr_chan == -1 ) 
		do_exit ( 1, "Permission denied to access the Data Base\n" );
	ipc_id = open_ipc ( curr_chan, sizeof (Request) );
	if ( ipc_id == NULL        && fprintf ( stderr, "Cannot open IPC\n" ) ||
		 ipc_id == ( IPC * )1  && fprintf ( stderr, "Server not started\n" ) ||
		 ipc_id == ( IPC * )-1 && fprintf ( stderr, "Permission denied\n" ) ) 
		 	exit ( 1 );
	for ( i = 0; cmd_list[i].cmd; i++ ) {
		if ( !strcmp ( argv[0], cmd_list[i].cmd ) ) {
			request.type = cmd_list[i].request;
			if ( argc != cmd_list[i].nargs ) {
				fprintf ( stderr, "Usage: %s\n",cmd_list[i].error );
				exit ( i + 1 );
			}
			break;
		}
	}
	if ( request.type != CMD_SHUTDOWN )
		request.acc_no = atoi ( argv[1] );
	size = OTHER_SIZE;
	switch ( request.type ) {
		case CMD_CREATE:
			strcpy ( request.name, argv[1] );
			strcpy ( request.phone, argv[2] );
			request.amount = atoi ( argv[3] );
			size = CREATE_SIZE;
			break;
		case CMD_DEPOSIT: case CMD_WITHDRAW:
			request.amount = atoi ( argv[2] );
			size = OTHER_SIZE;
			break;
		case CMD_CHANGE:
			strcpy ( request.phone, argv[2] );
			size = CHANGE_SIZE;
			break;
	}
	if ( send ( ipc_id, & request, size, 1 ) != IPC_SUCCESS )
		do_exit ( 2, "write-request error\n" );
	if ( request.type == CMD_SHUTDOWN ) { 
		close_ipc ( ipc_id );
		exit ( 0 );
	}
	if ( receive ( ipc_id, & reply ) != IPC_SUCCESS )
		do_exit ( 3, "read_reply Error\n" );
	if ( request.type == CMD_CREATE ) {
		if ( reply.result == 1 )
			printf ( "acc_no = %d\n", reply.info );
	}
	else if ( request.type == CMD_BALANCE ) {
		if ( reply.result == 1 ) 
			printf ( "Current balance %d\n", reply.info );
	}
	if ( reply.result == 0 ) 
		printf ( "%s\n", errors[reply.info] );
	else if ( reply.result == 1 )
		printf ( "Transaction Completed\n" );
	if ( dynamic_selection () ) {
		request.type = CMD_QUIT;
		if ( send ( ipc_id, & request, CONNECT_SIZE, 1 ) != IPC_SUCCESS )
			do_exit ( 2, "write-request error\n" );
	}
	close_ipc ( ipc_id );
	return 0;
}
