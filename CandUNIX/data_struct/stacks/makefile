STACK : stack.o v5.o 
	cc -o STACK stack.o v5.o

stack.o : stack.c stack.h
	cc -c stack.c

v5.o : v5.c stack.h
	cc -c v5.c

clean :
	-rm  -f stack.o v5.o STACK
