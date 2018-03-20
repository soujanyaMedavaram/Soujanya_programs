# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "selection.h"
# include "ipc.h"
# include "../sb.h"
# include "proto.h"

int max_channel ( ) {
	return 10;
}

int curr_channel ( ) {		// Will return 3, 4, ...
	IPC * ipc_id;
	Request request;
	Reply reply;

	ipc_id = open_ipc ( 2, sizeof (Request) );
	if ( ipc_id == NULL        && fprintf ( stderr, "Cannot open IPC\n" ) ||
		 ipc_id == ( IPC * )1  && fprintf ( stderr, "Server not started\n" ) ||
		 ipc_id == ( IPC * )-1 && fprintf ( stderr, "Permission denied\n" ) ) 
		 	exit ( 1 );
	request.type = 0;		// Channel No. request
	if ( send_ipc ( ipc_id, & request, CONNECT_SIZE, 1 ) != IPC_SUCCESS )
		return 1;
	if ( receive_ipc ( ipc_id, & reply ) != IPC_SUCCESS )
		return 2;
	close_ipc ( ipc_id );
	return reply.info;
}

int dynamic_selection ( void ) {
	return 1;
}
