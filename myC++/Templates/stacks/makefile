STACK : stack.o stack_app.o 
	c++ -o STACK stack.o stack_app.o

stack.o : stack.c++ stack.h
	c++ -c stack.c++

stack_app.o : stack_app.c++ stack.h
	c++ -c stack_app.c++

clean :
	rm -f STACK
	rm -f *.o
