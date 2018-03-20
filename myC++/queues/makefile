QUEUE : queue.o queue_app.o queue.h
	c++ -o QUEUE queue.o queue_app.o

queue.o : queue.c++ queue.h
	c++ -c queue.c++

queue_app.o : queue_app.c++ queue.h
	c++ -c queue_app.c++

clean :
	-@rm -f *.o
