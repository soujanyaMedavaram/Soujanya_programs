# include <stdio.h>
# include "nlist.h"

# define LENGTH		50

char line[LENGTH];
LIST *ld;
static int number;

static void help (void);
static void do_insert_in_list (void);
static void do_delete (void);
static void do_read_smallest (void);
static void do_read_smaller (void);
static void do_read_biggest (void);
static void do_read_bigger (void);
static void do_close_list (void);
static void do_total (void);
static void do_avg (void);
static void do_stats (void);
int compare_int(char *data1, char *data2)
{
	return *(int *)data1 - *(int *)data2;
}
main()
{
	register char *p;
	 
	ld = open_list(sizeof(number),compare_int );
	if (ld == L_FAIL)
	{
		fprintf(stderr,"can't create list\n");
		exit(1);
	}
	while (1)
	{
		printf("list option :");
		if (fgets(line, LENGTH,stdin) == NULL) exit(2);
		for ( p = line; *p == ' ' || *p == '\t'; p++)
			;
		switch(*p)
		{
			case 'h':case 'H':
			default:
				help();
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				number = atoi(p);
				do_insert_in_list();
				break;
			case 'f': case 'F': do_read_smallest(); break;
			case 'l': case 'L':	do_read_biggest(); break;
			case 'n': case 'N': do_read_smaller(); break;
			case 'p': case 'P': do_read_bigger(); break;
			case 't': case 'T': do_total (); break;
			case 'a': case 'A': do_avg (); break;
			case 's': case 'S': do_stats(); break;
			case 'e': case 'E': 
				reset_transferred(ld);
				if (close_list (ld) == L_SUCCESS)
				exit (0);
				else printf("some thing wrong in closing\n");

			case 'd': case 'D':do_delete(); break;
		}
	}
}

static void help()
{
	printf ("USe the following\n");
	printf ("	<number> <cr> to append\n");
	printf ("	e <cr> to exit from program\n");
	printf ("	h <cr> to print this help message\n");
	if(list_empty(ld)) return;
	printf ("	f <cr> to read smallest number\n");
	printf ("	l <cr> to read biggest number\n");
	printf ("	n <cr> to read smaller number\n");
	printf ("	p <cr> to read biggerious number\n");
	printf ("	d <cr> to delete a number\n");
	printf ("	t <cr> for total of numbers in,list\n");
	printf ("	a <cr> for average of numbers in list\n");
	printf ("	s <cr> for total transactions on the list\n");

}

static void do_insert_in_list ()
{
	if (insert_in_list (ld,(char *)&number) == L_SUCCESS)
		printf("ok\n");
	else printf("can not append\n");
}

static void do_read_smallest()
{
	if (list_empty(ld))
		printf(" you need to append some numbers\n");
	else if(read_smallest(ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf ("something wrong no more items\n");
}

static void do_read_smaller ()
{
	if (list_empty(ld))
		printf("you need to append some numbers \n");
	else if (read_smaller (ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf("some thing wrong! no more items\n");
}

static void do_read_biggest()
{
	if (list_empty(ld))
		printf ("you need to append some numbers\n");
	else if(read_biggest(ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf("something wrong! no kore items\n");
}

static void do_read_bigger()
{
	if (list_empty(ld))
		printf("you need to append some numbers \n");
	else if (read_bigger(ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf("some thing wrong! no more items\n");
}

static void do_delete()
{
	if (list_empty(ld))
		printf("empty list\n");
	else if (delete(ld) == L_SUCCESS) printf ("ok\n");
	else printf("you have to read item before delete\n");
}

void do_total()
{
	long total;
	if (list_empty(ld))
		printf ("empty list\n");
	else 
	{
		total = tot_cal(ld);
		printf("\n total of list elements is %ld",total);
	}
}

void do_avg()
{
	double avg;
	if (list_empty(ld))
		printf ("\n list idempty\n");
	else
	{
		avg = avg_cal(ld);
		printf("\n average of elements in list is %lf\n",avg);
	}
}


void do_stats()
{
	long stats;
	stats = stats_cal(ld);
	printf("the total no of transactions are %ld",stats);
}
	
