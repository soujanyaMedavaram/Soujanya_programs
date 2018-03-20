//	client.c

# include <stdio.h>
# include <stdlib.h>
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
	{ "quit",     CMD_QUIT,     1, "quit" },
	{ "shutdown", CMD_SHUTDOWN, 1, "shutdown" },
	{ NULL }
};

main ( int argc, char *argv[] ) {
	Request request;
	Reply reply;
	int i, curr_chan;
	FILE * fp;
	IPC  * ipc_id;
	int size, x;
	int nargs;
	char *line, **cmd,  *word ;

	curr_chan = curr_channel ( );
	if ( curr_chan == -1 ) 
		do_exit ( 1, "Permission denied to access the Data Base\n" );
	ipc_id = open_ipc ( curr_chan, sizeof (Request) );
	if ( ipc_id == NULL        && fprintf ( stderr, "Cannot open IPC\n" ) ||
		 ipc_id == ( IPC * )1  && fprintf ( stderr, "Server not started\n" ) ||
		 ipc_id == ( IPC * )-1 && fprintf ( stderr, "Permission denied\n" ) ) 
		 	exit ( 1 );
	while ( 1 ) {
		printf ( "<request> " );
		line = get_line ( stdin );
		if ( !line ) continue;
		nargs = 0;
		cmd = NULL;
		while ( (word = get_word ( line ) ) != NULL ) {
			line = NULL;
			cmd = realloc ( cmd, (nargs + 1 ) * sizeof ( char * ) );
			cmd[nargs++] = strdup ( word );
		}
		if ( !nargs ) continue;
		for ( i = 0; cmd_list[i].cmd; i++ ) {
			if ( !strcmp ( cmd[0], cmd_list[i].cmd ) ) {
				request.type = cmd_list[i].request;
				if ( nargs != cmd_list[i].nargs ) {
					fprintf ( stderr, "Usage: %s\n",cmd_list[i].error );
					exit ( i + 1 );
				}
				break;
			}
		}
		if ( cmd_list[i].cmd == NULL ) {
			printf ( "Allowed Transactions are \n" );
			for ( i = 0; cmd_list[i].cmd; i++ )
				printf ( "%s\n", cmd_list[i].error );
			continue;
		}
		if ( request.type != CMD_SHUTDOWN && request.type != CMD_QUIT )
			request.acc_no = atoi ( cmd[1] );
		size = OTHER_SIZE;
		switch ( request.type ) {
			case CMD_CREATE :
				strcpy ( request.name, cmd[1] );
				strcpy ( request.phone, cmd[2] );
				request.amount = atoi ( cmd[3] );
				size = CREATE_SIZE;
				break;
			case CMD_DEPOSIT : case CMD_WITHDRAW :
				request.amount = atoi ( cmd[2] );
				size = OTHER_SIZE;
				break;
			case CMD_CHANGE :
				strcpy ( request.phone, cmd[2] );
				size = CHANGE_SIZE;
				break;
				
		}
		if ( send_ipc ( ipc_id, & request, size, 1 ) != IPC_SUCCESS )
			do_exit ( 2, "write-request error\n" );
		if ( request.type == CMD_SHUTDOWN  || request.type == CMD_QUIT ) { 
			close_ipc ( ipc_id );
			exit ( 0 );
		}
		if ( (receive_ipc ( ipc_id, & reply ) )!= IPC_SUCCESS ) {
			do_exit ( 3, "read_reply Error\n" );
		}
		if ( reply.result == 1 ) {
			if ( request.type == CMD_CREATE )
				printf ( "acc_no = %d\n", reply.info );
			else if ( request.type == CMD_BALANCE )
				printf ( "Current balance %d\n", reply.info );
			printf ( "Transaction Completed\n" );
		} else printf ( "%s\n", errors[reply.info] );
		for ( i =0; i < nargs; i++ )
			free ( cmd[i] );
		free ( cmd );
	}
	return 0;
}
