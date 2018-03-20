# include <stdio.h>

struct student
{
	char name[10];
	int abc;
	char ch;
	long l1;
};

main()
{
	struct sudent student;
	student.name = "ahi";
	student.abc = 10000;
	student.ch = 'a';
	student.l1 = 1000000;
	printf ("size of name is %d",sizeof(student.name));
	printf ("size of int is %d", sizeof(student.abc));
	printf ("size of char is %d",sizeof(student.ch));
	printf ("size of long is %d",sizeof(student.l1));
	printf ("size of structure is %d",sizeof(student));
}
