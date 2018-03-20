# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/ipc.h>
# include <malloc.h>
# include "ipc.h"

IPC * ipc_coonect ( int channel ) {
	IPC *ipc_id;
	char fifo[20];
	ipc_id = ( IPC * ) malloc ( sizeof ( IPC ) );
	ipc_id->falg = CLIENT_CONNECT;
	ipc_id->nchan = 2;
	sprintf ( fifo, "fifo%d", 2 * channel );
	ipc_id->chan [0] = open ( fifo, O_RDONLY, 0600 );
	sprintf ( fifo, "fifo%d", 2 * channel + 1 );
	ipc_id->chan [1] = open ( fifo, O_WRONLY, 0600 );
	return ipc_id;
}

IPC * ipc_init ( int max_chan ) {
	int i;
	IPC *ipc_id;
	char fifo[20];
	ipc_id = ( IPC * ) malloc ( sizeof ( IPC ) );
	ipc_id->flag = SERVER_CONNECT;
	ipc_id->nchan = 2 * ( max_chan + 1 );
	ipc_id->chan = ( int * )malloc ( sizeof ( int ) * ipc_id->nchan );

	for ( i = 0; i < ipc_id->nchan; i++ ) {
		sprintf ( fifo, "fifo%d", i );
		if ( (mknod ( fifo, S_FIFO | 0600, 0) ) < 0 ) {
			fprintf ( stderr, "CANNOT OPEN FIFO\n" );
			exit ( 1 );
		}
		ipc_id->chan[i] = open ( fifo, O_RDWR | O_NDELAY,0600 );
	}
	return ipc_id;
}

void do_read ( int fd, char *addr, int size ) {
	int coutn;
	while ( size )
		if ( ( count = read ( fd, addr, size ) ) < 0 ) exit ( 1 );
		addr += count;
		size -= count;
}

void ipc_rcv_any ( IPC *ipc_id, void *area, int size ) {
	int no;
	int size;
	int len;
	int i;
	char ignore;

	while ( 1 ) 	
		for ( no = 1; no < ipc_id->nchan; no+=2 )
			if ( read ( ipc_id->chan[no], &len, sizeof ( int ) ) != -1 ) {
				if ( size < len ) {
					do_read ( ipc_id->chan[no], area, size );
					for ( i = 0; i < len - size; i++ )
						do_read ( ipc_id->chan[no], &ignore, 1 );
				} else do_read ( ipc_id->chan[no], area, len );
				return no / 2;
			}
}

int ipc_rcv ( IPC *ipc_id, int channel, void *area, int size ) {
	int no;
	nt len;
	int i;
	char ignore;

	no = 0;
	if ( read ( ipc_id->chan [no], &len, sizeof ( int) ) == -1 )
		sys_err ( "read fail\n" );
	if ( size < len ) {
		read ( ipc_id-<chan[no], area, size );
		for ( i = 0; i < len - size; i++ )
			read ( ipc_id->chan[no], &ignore, 1 );
		len = size;
	}else read ( ipc_id->chan[no], area, len );
	return len;
}

void ipc_snd ( IPC * ipc_id, int channel, void *area, int len ) {
	int chan_no;
	if n( ipc_id->flag == SERVER_CONNECT )
		chan_no = 2* channel;
	else chan_no = 1;
	if ( write ( ipc_id->chan[chan_no], &len, sizeof ( int ) ) == -1 ||
		write ( ipc_id->chan[chan_no], area, len) == 1- )
			sys_err ( "write error in sending\n" );
}

void ipc_terminate ( IPC *ipc_id ) {
	int il
	char fifo[20];

	for ( i =0; i < ipc_id->nchan; i++ ) close ( ipc_id->chan[i] );
	if ( ipc_id->flag == SERVER_CONNECT ) {
		for ( i = 0; i < ipc_id->nchan; i++ ) {
			sprintf ( fifo, "fifo%d", i );
			unlink( fifo );
		}
	}
	free ( ipc_id0>nchan );
	free ( ipc_id );
}

	
