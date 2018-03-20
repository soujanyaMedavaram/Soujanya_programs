# Select channel selection method by proper uncommenting

SELECTION=static
#SELECTION=dynamic

SRC=../
all : server create deposit withdraw change balance shutdown

server : $(SRC)server.c $(SRC)ipc.h $(SRC)proto.h ../../sb.h \
			msg.o utils.o $(SELECTION).o
	cc -o server $(SRC)server.c $(SELECTION).o msg.o utils.o

msg.o : msg.c $(SRC)ipc.h $(SRC)proto.h ../../sb.h
	cc -c msg.c

sem.o:	$(SRC)sem.c $(SRC)sem.h
	cc -c $(SRC)sem.c

utils.o:	../../../utils.c
	cc -c ../../../utils.c

create : $(SRC)client.c $(SRC)ipc.h $(SRC)proto.h $(SRC)sem.h ../../sb.h \
		utils.o $(SELECTION).o msg.o sem.o
	cc -o create $(SRC)client.c utils.o $(SELECTION).o msg.o sem.o

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

shutdown : create
	@-rm -f shutdown 
	ln create shutdown

static.o : $(SRC)static.c $(SRC)selection.h $(SRC)config
	cc -c $(SRC)static.c

dynamic.o: $(SRC)dynamic.c $(SRC)selection.h $(SRC)ipc.h
	cc -c $(SRC)dynamic.c

clean:
	@-rm create change balance shutdown deposit withdraw 2> /dev/null
	@-rm server 2> /dev/null
	@-rm static.o 2> /dev/null
	@-rm dynamic.o 2> /dev/null
	@-rm utils.o 2> /dev/null
	@-rm sem.o 2> /dev/null
	@-rm msg.o 2> /dev/null

