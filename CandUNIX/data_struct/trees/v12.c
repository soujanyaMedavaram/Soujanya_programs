# include <stdio.h>
# include "tree.h"
# define LENGTH 50

TREE *td;
char line[LENGTH];
static int number;

int compare_int (char *, char *);
void print_leaves (register TREE *);
int find_total (register TREE *);
void search (register TREE *);
void help (void);

main() {
	register char *p;

	td = open_tree (sizeof (number), compare_int);
	if (td == T_FAIL) exit(1);
	while (1) {
		printf ("tree option: ");
		if (!fgets (line, LENGTH, stdin))
			exit(2);
		for (p = line; *p == ' ' || *p == '\t' ; p++);
		switch (*p) {
			case '\n' : continue;
			case 'h' : case 'H' :
			default : help (); break;
			case '0' : case '1' : case '2' : case '3' : case '4' :case '5':
			case '6' : case '7' : case '8' : case '9' :
				number = atoi (p);
				if (add_leaf(td, (char *) &number) == T_SUCCESS)
					printf ("ok\n");
				else printf ("insertion problem\n");
				break;
			case 'f' :
				if (read_first (td, (char *) &number) == T_SUCCESS)
					printf("%d\n", number);
				else printf ("something wrong\n");
				break;
			case 'n' :
				if (read_next (td, (char *) &number) == T_SUCCESS)
					printf ("%d\n", number);
				else printf ("something wrong \n");
				break;
			case 'p' : print_leaves (td); break;
			case 't' : printf ("total = %d\n", find_total(td)); break;
			case 's' : search (td); break;
			case 'e' : exit(0);
		}
	}
	close_tree(td);
}
void help() {
	printf ("<num> to insert\n");
	printf ("'f' to read first element\n"); 
	printf ("'n' to read next element\n");
	printf ("'p' to print leaves, 't' to print total, 's' to search\n");
	printf ("'e' to exit\n");
}
void print_leaves (TREE *td) {
	void print_leaf (char *, void *);
	navigate (td, print_leaf, (void *) td);
}

void print_leaf (char *data, void *app_data) {
	printf ("%d\n", *(int *) data);
}

int find_total (TREE *td) {
	int total;
	void add_to_total (char *, void *);
	total = 0;
	navigate (td, add_to_total, (void *)&total);
	return total;
}

void add_to_total (char *data, void *app_data) {
	*(int *) app_data += *(int*) data;
}

void search (TREE *td) {
	int number;
	void search_leaf (char *, void *);

	printf ("enter number to be searched : ");
	scanf ("%d", &number);
	navigate (td, search_leaf, (void *) &number);
}
void search_leaf (char *data, void *app_data) {
	if ( *(int*) app_data == *(int *) data )
		printf ("number is present\n");
	else printf ("\n element is not present");
}
int compare_int (char *data1, char *data2) {
	return *(int *) data1 - *(int *) data2;
}
