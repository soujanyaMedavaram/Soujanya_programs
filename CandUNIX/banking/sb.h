//	sb.h	: savings bank accounting

# define NAME_LEN	50		// Max. Customer name length
# define PHONE_LEN	15		// Max. Phone number length

typedef struct {
	int acc_no;
	char name [NAME_LEN];
	char phone [PHONE_LEN];
	int  balance;
} Account;

# define datafile	"info.data"

void do_exit ( int exit_code, char *msg );

// Command flag values

# define CMD_ERROR		0
# define CMD_WITHDRAW	1
# define CMD_DEPOSIT	2
# define CMD_BALANCE	3
# define CMD_CHANGE		4


# define CREATE			1
# define DEPOSIT		2
# define WITHDRAW		3
# define CHANGE			4
# define BALANCE		5
