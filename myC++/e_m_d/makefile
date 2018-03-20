EMD : derived_class.o date.o EmpMgrDir.o
	c++ -o EMD derived_class.o EmpMgrDir.o date.o

derived_class.o : derived_class.c++ derived_class.h 
	c++ -c derived_class.c++ 

date.o : ../operator_overloading/date.c++ ../operator_overloading/date.h
	c++ -c ../operator_overloading/date.c++

EmpMgrDir.o : EmpMgrDir.c++ derived_class.h
	c++ -c EmpMgrDir.c++

clean :
	rm -f EMD
	rm -f *.o
