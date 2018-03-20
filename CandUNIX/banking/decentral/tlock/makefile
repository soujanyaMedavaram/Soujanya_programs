all : create deposit withdraw change balance startup shutdown

create : create.c lock.c ../../sb.h ../../do_exit.c
	cc -o create create.c lock.c ../../do_exit.c

deposit : deposit.c lock.c ../../sb.h ../../do_exit.c
	cc -o deposit deposit.c lock.c ../../do_exit.c

withdraw : withdraw.c lock.c ../../sb.h ../../do_exit.c
	cc -o withdraw withdraw.c lock.c ../../do_exit.c

change : change.c lock.c ../../sb.h ../../do_exit.c
	cc -o change change.c lock.c ../../do_exit.c

balance : balance.c ../../sb.h ../../do_exit.c
	cc -o balance balance.c ../../do_exit.c

startup : startup.c ../../sb.h ../../do_exit.c
	cc -o startup startup.c ../../do_exit.c

shutdown : shutdown.c ../../sb.h ../../do_exit.c
	cc -o shutdown shutdown.c ../../do_exit.c
	
