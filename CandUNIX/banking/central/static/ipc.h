typedef struct ipc IPC;

# define IPC_SUCCESS	0
# define IPC_FAIL		1

IPC * create_ipc ( int max_chl ) ;
IPC * open_ipc ( int curr_chl ) ;
int read_request ( IPC *ipc_id, void *req, int size );
int write_request ( IPC *ipc_id, void *req , int size );
int write_reply ( IPC *ipc_id, void *rep, int size , int channel);
int read_reply ( IPC *ipc_id, void *rep, int size );
void remove_ipc ( IPC *ipc_id, int max_chl , int fd_db );
void close_client ( IPC *ipc_id, int curr_chl );

//int fd[50];
