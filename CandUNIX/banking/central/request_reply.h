# define NAME_LEN	50	
# define PHONE_LEN	15
# define MSG_LEN	100

typedef struct {
	int type;
	int rep_chl;
	int amount;
	int acc_no;
	char cust_name[NAME_LEN];
	char phone[PHONE_LEN];
} Request;

typedef struct {
	int result;
	char msg[MSG_LEN];
	int acc_no;
	int amount;
	char phone[PHONE_LEN];
} reply;
