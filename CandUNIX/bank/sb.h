//	sb.h	: savings bank accounting
# ifndef _SB_H
# define _SB_H

# define NAME_LEN	50		// Max. Customer name length
# define PHONE_LEN	15		// Max. Phone number length
# define datafile	"info.data"

typedef struct {
	int acc_no;
	char name [NAME_LEN];
	char phone [PHONE_LEN];
	int  balance;
} Account;

// Command / Request flag values
// Request zero is reserved. ( Used for channel number request )

# define CMD_CONNECT	0
# define CMD_CREATE		1
# define CMD_DEPOSIT	2
# define CMD_WITHDRAW	3
# define CMD_CHANGE		4
# define CMD_BALANCE	5
# define CMD_QUIT		6
# define CMD_SHUTDOWN	7

# endif //_SB_H
