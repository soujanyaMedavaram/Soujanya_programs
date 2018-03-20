all : server create withdraw deposit change balance shutdown

server : server.c ../../request.h ../../../sb.h ../../../do_exit.c
	cc -o server server.c ../../../do_exit.c

create : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	cc -o create client.c ../../../do_exit.c

withdraw : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	@-rm -f withdraw
	ln create withdraw
	
deposit : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	@-rm -f deposit
	ln create deposit 

change : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	@-rm -f change
	ln create change
	
balance : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	@-rm -f balance
	ln create balance

shutdown : client.c ../../request.h ../../../sb.h ../../../do_exit.c
	cc -o shutdown shutdown.c ../../../do_exit.c

