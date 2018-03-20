# ifndef _PROTO_H
# define _PRORO_H

//	proto.h
//		Must include sb.h before this file
// CREATE_SIZE uses whole memory of Request structure
// CHANGE_SIZE uses sizeof structure up to phone. ( including phone )
// OTHER_SIZE  uses  sizeof structure upto amount. ( incliding amount )

typedef struct {
	int  type;
	int  acc_no;
	int  amount;
	char phone[PHONE_LEN];
	char name[NAME_LEN];
} Request;

# define OFFSET(Struct, member)	( (int) & ((Struct *) 0) -> member )
# define CONNECT_SIZE	OFFSET (Request, acc_no )
# define CREATE_SIZE	sizeof (Request)
# define CHANGE_SIZE	OFFSET (Request, name[0] )
# define OTHER_SIZE		OFFSET (Request, phone[0] )

typedef struct {
	int  result;
	int  info;
} Reply;

#endif //_PROTO_H
