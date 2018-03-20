# include <stdio.h>

struct student
{
	char name[10];
	int sno;
	long marks;
	double percent;
	int m1, m2;
};
struct emp
{ }e1;

main()
{
	struct student s1;
	printf ("size of name - char is %d\n",sizeof(s1.name));
	printf ("size of sno - int is %d \n",sizeof(s1.sno));
	printf ("size of marks is - long %d\n",sizeof(s1.marks));
	printf ("size of percent is - double %d\n",sizeof(s1.percent));
	printf ("size of m1 and m2 is - int %d %d\n",sizeof(s1.m1),sizeof(s1.m2));
	printf ("\n size of %d\n",sizeof(s1));
	printf ("\n size of empty emp is %d\n",sizeof(e1));
}
