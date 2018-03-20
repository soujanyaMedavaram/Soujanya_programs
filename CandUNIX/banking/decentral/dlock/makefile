#all:
#	cd ../;  $(MAKE)

all : create deposit withdraw change balance
create :  create.c ../../sb.h
	cc -o create create.c ../../do_exit.c

withdraw : withdraw.c ../../sb.h
	cc -o withdraw withdraw.c ../../do_exit.c

deposit : deposit.c ../../sb.h
	cc -o deposit deposit.c ../../do_exit.c

change : change.c ../../sb.h 
	cc -o change change.c ../../do_exit.c

balance : balance.c ../../sb.h
	cc -o balance balance.c ../../do_exit.c
