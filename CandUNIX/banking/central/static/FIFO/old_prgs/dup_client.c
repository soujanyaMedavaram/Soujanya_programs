# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../../request.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define REQ_FIFO	"req_fifo"

main ( int argc, char **argv ) {
	char *rep_fifo, *conf_fifo, *line;
	int fd_read, fd_write;
	FILE *fp;
	Request req;
	int cr_flag, wd_flag, dp_flag, ch_flag, bl_flag;
	int per_flag = 0;
	
	cr_flag = wd_flag = dp_flag = ch_flag = bl_flag = 1;
	fp = fopen ( "config.sb", "r" );
	if ( fp == NULL ) 
		do_exit ( 1, "No permissin to read configaration file\n" );
	while ( 1 ) {
		if ( !fgets ( line, 100, fp ) )
			break;
		rep_fifo = strtok ( line, " " );
		if ( !strcmp ( req.rep_name, rep_fifo ) ) {
			rep_fifo = strdup ( strtok ( NULL , " ") );
			per_flag = 1;
			break;
		}
	}
	fclose ( fp );
	if ( !per_flag ) 
		do_exit ( 2, "permission denied to perform operation\n" ); 
	fd_write = open ( REQ_FIFO, O_WRONLY );
	if ( fd_write < 0 ) 
		do_exit ( 3, "read permissin denied in current directory\n" );
	cr_flag = strcmp ( argv[0], "create" );
	dp_flag = strcmp ( argv[0], "deposit" );
	wd_flag = strcmp ( argv[0], "withdraw" );
	ch_flag = strcmp ( argv[0], "change" );
	bl_flag = strcmp ( argv[0], "balance" );
	if ( !cr_flag && argc != 4 )
		do_exit ( 4, "Usage : create <name> <phone_num> <balance>\n" );
	else if ( ( !dp_flag || !wd_flag ) && argc != 3 )
		do_exit ( 5, "Usage: deposit/withdraw <acc_no> <balance>\n" );
	else if ( !ch_flag && argc != 3 )
		do_exit ( 6, "Usage: change <acc_no> <phone_num>\n" );
	else if ( !bl_flag && argc != 2)
		do_exit ( 7, "Usage: balance <acc_no>\n" );
	strcpy ( req.rep_name, rep_fifo );
	strcpy ( req.cmd_name, argv[0] );
	if ( !wd_flag || !dp_flag || !bl_flag || !cr_flag || !ch_flag ) {
		strcpy ( req.arg_accno , argv[1] );
		if ( !wd_flag || !dp_flag )
			strcpy ( req.amount , argv[2] );
		else if ( !cr_flag ){
			strcpy ( req.cust_name , argv[1] );
			strcpy ( req.phone_num, argv[2] );
			strcpy ( req.amount , argv[3] );
		}
		if ( !ch_flag )
			strcpy ( req.phone_num, argv[2] );
	}
	else do_exit ( 8, "invalid operation\n" ); 
	close ( fd_write );
	fd_read = open ( rep_fifo, O_RDONLY );
	read ( fd_read, conf_fifo, 100 );
	fprintf ( stdout, "%s\n", conf_fifo );
	close ( fd_read );
	return 0;
}
