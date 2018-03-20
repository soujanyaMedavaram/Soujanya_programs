typedef struct {
	int flag;
# define SERVER_CONNECT		0
# define CLIENT_CONNECT		1
int nchan;
int *chan;
} IPC;

IPC * ipc_init ( int max_chan );
IPC * ipc_connect ( int chan );
void ipc_terminate ( IPC *ipc_id );
int ipc_rcv_any ( IPC * ipc_id, void *area, int size );
int ipc_rcv ( IPC * ipc_id, int channel, void *area, int size );
void ipc_snd ( IPC *ipc_id, int channel, void *aea, int length );

