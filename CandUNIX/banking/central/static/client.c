# include <stdio.h>
# include "ipc.h"
# include "../request_reply.h"
# include "../../sb.h"
# include <string.h>

const struct {
	char * cmd;
	int reqst;
	int nargs;
	char * error;
} cmd_list[] = { 
	{ "create", 1, 4, "create <name> <phone> <balance>" },
	{ "deposit", 2, 3, "deposit <acc_no> <amount>" },
	{ "withdraw", 3, 3, "withdraw <acc_no> <amount>" },
	{ "change", 4, 3, "change <acc_no> <amount>" },
	{ "balance", 5, 2, "balance <acc_no>" },
	{ NULL }
};

main ( int argc, char *argv[] ) {
	Request req;
	reply rep;
	int i, curr_chl;
	char *msg;
	FILE *fp;
	IPC *ipc_id;

	fp = fopen ( "ser_pid", "r" );
	if ( fp == NULL )
		do_exit ( 1, "server not started up\n" );
	fclose ( fp );
	for ( i =0; cmd_list[i].cmd; i++ ) {
		if ( !strcmp ( argv[0], cmd_list[i].cmd ) ) {
			req.type = cmd_list[i].reqst;
			if ( argc != cmd_list[i].nargs ) {
				fprintf ( stderr, "Usage: %s\n",cmd_list[i].error );
				exit ( i + 1 );
			}
			break;
		}
	}
	if ( !cmd_list[i].cmd ) {
		fprintf ( stderr, "commands are\n" );
		for ( i = 0; cmd_list[i].cmd; i++ )
			fprintf ( stderr, "\t %d %s\n", (i + 1), cmd_list[i].cmd );
		exit ( 1 );
	}
	req.acc_no = atoi ( argv[1] );
	switch ( req.type ) {
		case 1:
			strcpy ( req.cust_name , argv[1] );
			strcpy ( req.phone, argv[2] );
			req.amount = atoi ( argv[3] );
			break;
		case 2: case 3:
			req.amount = atoi ( argv[2] );
			break;
		case 4:
			strcpy ( req.phone, argv[2] );
			break;
		case 5:
			break;
	}
	curr_chl = curr_channel ( );
	ipc_id = open_ipc ( curr_chl );
	if ( ipc_id == NULL )
		do_exit (1, "open ipc failed\n" );
	req.rep_chl = curr_chl;
	if ( write_request ( ipc_id, &req , sizeof ( req ) ) != IPC_SUCCESS )
		do_exit ( 2, "write- request error\n" );
	if ( read_reply ( ipc_id, &rep, sizeof ( rep ) ) != IPC_SUCCESS )
		do_exit ( 3, "read_reply Error\n" );
	if ( req.type == CREATE ) {
		if ( rep.result == 1 )
			printf ( "acc_no = %d\n", rep.acc_no );
	}
	else if ( req.type == CHANGE ) {
		if ( rep.result == 1 )
			printf ( "new phone number %s\n", rep.phone );
	}
	else if ( req.type == BALANCE ) {
		if ( rep.result == 1 )
			printf ( "Current balance %d\n", rep.amount );
	}
	if ( rep.result == 0 ) 
		printf ( "%s\n", rep.msg );
	else if ( rep.result == 1 )
		printf ( "Transaction Completed\n" );
	close_client ( ipc_id, curr_chl );
	return 0;
}
