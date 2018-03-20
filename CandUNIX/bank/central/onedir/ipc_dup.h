//	ipc.h
# ifndef	_IPC_H
#	define	_IPC_H

typedef struct ipc IPC;

# define IPC_SUCCESS	0
# define IPC_FAIL		-1

IPC * create_ipc ( int max_channel, int max_msg_size );
IPC * open_ipc   ( int channel, int max_msg_size );
int  send_ipc    ( IPC * ipc_id, void * data, int size, int channel );
int  receive_ipc ( IPC * ipc_id, void * data );
void close_ipc  ( IPC * ipc_id );

# endif	// _IPC_H
