# include <stdio.h>
# include "listc.h"

# define LENGTH		50

char line[LENGTH];
LIST *ld;
static int number;

static void help (void);
static void do_append (void);
static void do_delete (void);
static void do_read_first (void);
static void do_read_next (void);
static void do_read_last (void);
static void do_read_prev (void);
static void do_close_list (void);
static void do_total (void);
static void do_avg (void);
static void do_minmax (void);
static void do_stats (void);

main()
{
	register char *p;
	 
	ld = open_list(sizeof(number));
	if (ld == L_FAIL)
	{
		fprintf(stderr,"can't create list\n");
		exit(1);
	}
	while (1)
	{
		printf("list option :");
		if (fgets(line, LENGTH,stdin) == NULL) exit(2);
		for ( p = line; *p == ' ' || *p == '\t'; p++);
		switch(*p)
		{
			case 'h':case 'H':
			default:
				help();
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				number = atoi(p);
				do_append();
				break;
			case 'f': case 'F': do_read_first(); break;
			case 'l': case 'L':	do_read_last(); break;
			case 'n': case 'N': do_read_next(); break;
			case 'p': case 'P': do_read_prev(); break;
			case 't': case 'T': do_total (); break;
			case 'a': case 'A': do_avg (); break;
			case 'm': case 'M': do_minmax();break;
			case 's': case 'S': do_stats(); break;
			case 'e': case 'E': 
				reset_transferred(ld);
				printf ("Still in list\n");
				while (read_next (ld, (char *)&number) == L_SUCCESS)
					printf("\t%d\n",number);
				exit (0);

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
	printf ("	f <cr> to read first number\n");
	printf ("	l <cr> to read last number\n");
	printf ("	n <cr> to read next number\n");
	printf ("	p <cr> to read previous number\n");
	printf ("	d <cr> to delete a number\n");
	printf ("	t <cr> for total of numbers in,list\n");
	printf ("	a <cr> for average of numbers in list\n");
	printf ("	m <cr> for minimum and maximum in list\n");
	printf ("	s <cr> for total transactions on the list\n");

}

static void do_append ()
{
	if (append (ld,(char *)&number) == L_SUCCESS)
		printf("ok\n");
	else printf("can not append\n");
}

static void do_read_first()
{
	if (list_empty(ld))
		printf(" you need to append some numbers first\n");
	else if(read_first(ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf ("something wrong no more items\n");
}

static void do_read_next ()
{
	if (list_empty(ld))
		printf("you need to append some numbers first\n");
	else if (read_next (ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf("some thing wrong! no more items\n");
}

static void do_read_last()
{
	if (list_empty(ld))
		printf ("you need to append some numbers first\n");
	else if(read_last(ld,(char *)&number) == L_SUCCESS)
		printf("%d\n",number);
	else printf("something wrong! no kore items\n");
}

static void do_read_prev()
{
	if (list_empty(ld))
		printf("you need to append some numbers first\n");
	else if (read_prev(ld,(char *)&number) == L_SUCCESS)
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

void do_minmax()
{
	if (list_empty(ld))
		printf("list is empty\n");
	else
		min_max(ld);
}

void do_stats()
{
	long stats;
	stats = stats_cal(ld);
	printf("the total no of transactions are %ld",stats);
}
	
