LIST :list.o list_app.o
	c++ -o LIST list.o list_app.o

list.o : list.c++ list.h
	c++ -c list.c++

list_app.o : list_app.c++ list.h
	c++ -c list_app.c++

clean :
	rm -f LIST
	rm -f *.o
