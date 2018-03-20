all : create deposit withdraw change balance startup shutdown

create : create.c lock.c ../../sb.h utils.o
	cc -o create create.c lock.c utils.o

utils.o : ../../../utils.c
	cc -c ../../../utils.c

deposit : deposit.c lock.c ../../sb.h utils.o
	cc -o deposit deposit.c lock.c utils.o

withdraw : withdraw.c lock.c ../../sb.h utils.o
	cc -o withdraw withdraw.c lock.c utils.o

change : change.c lock.c ../../sb.h utils.o
	cc -o change change.c lock.c utils.o

balance : balance.c ../../sb.h utils.o
	cc -o balance balance.c utils.o

startup : startup.c ../../sb.h utils.o
	cc -o startup startup.c utils.o

shutdown : shutdown.c ../../sb.h utils.o
	cc -o shutdown shutdown.c utils.o
	
