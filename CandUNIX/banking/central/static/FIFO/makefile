all : server create deposit withdraw change balance shutdown

server : ../server.c ../ipc.h config.o ../../../sb.h ../../request_reply.h \
			fifo.o do_exit.o
	cc -o server ../server.c config.o fifo.o do_exit.o

config.o : ../config.h ../config.c ../config.sb
	cc -c ../config.c

fifo.o : ../ipc.h ../../../sb.h ../../request_reply.h fifo.c
	cc -c fifo.c

do_exit.o:	../../../do_exit.c
	cc -c ../../../do_exit.c

create : ../client.c ../../../sb.h ../ipc.h ../../request_reply.h \
		do_exit.o config.o fifo.o
	cc -o create ../client.c do_exit.o config.o fifo.o

deposit : create
	@-rm -f deposit
	ln create deposit

withdraw : create
	@-rm -f withdraw
	ln create withdraw

change : create
	@-rm -f change 
	ln create change

balance : create
	@-rm -f balance 
	ln create balance

shutdown : ../shutdown.c do_exit.o
	cc -o shutdown ../shutdown.c do_exit.o
