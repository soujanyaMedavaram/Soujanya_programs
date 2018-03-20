# include <stdio.h>
# include <stdlib.h>

struct node {
	int data;
	struct node *next;
};
typedef struct node Node;

Node *Lptr = NULL;

int add ( int i ) {
	Node *ins = (Node *) malloc ( sizeof (Node));
	ins -> data = i;
	ins -> next = Lptr;
	Lptr = ins;
	return 1;
}

int display () {
	Node *temp = Lptr;
	while (temp) {
		printf ("-> %d ",temp->data);
		temp = temp -> next;
	}
	printf ("\n");
	return 2;
}

// Solution 1 : Brilliant and Elegant

/*int findloop () {
	Node *temp = Lptr, *fp, *sp;
	int ret = 0;

	fp = Lptr;
	if ( !fp ) return 0;
	sp = fp -> next;
	while ( fp -> next ) {
		if ( fp == sp ) {
			ret = 1;
			break;
		}
		sp = sp -> next;
		if ( !sp ) break;
		if ( fp == sp ) {
			ret = 1;
			break;
		}
		fp = fp -> next;
		sp = sp -> next;
		if ( !sp ) break;
	}
	return ret;
}
*/

void makeloop ( Node * Lptr ) {
	Node * temp = Lptr;

	if ( !Lptr ) return;
	while ( temp -> next ) temp = temp -> next;
	temp -> next = Lptr;
}

// Solution 2 : Simpler ( but assumes all addresses are even )

Node * findloop ( Node * Lptr ) {
	Node * temp = Lptr;
	Node * tmp = Lptr;
	int ret;

	if ( !temp ) return NULL;
	while ( temp -> next  ) {
		if ( (unsigned) temp -> next & 1 ) {
			ret = 1;
			break;
		}
		tmp = temp -> next;
		temp -> next = (Node *) ( (unsigned) temp -> next ^ 1 );
		temp = tmp;
		ret = 0;
	}
	temp = Lptr;
	while ( (unsigned) temp -> next & 1 ) {
		temp -> next = (Node * ) ( (unsigned) temp -> next ^ 1 );
		temp = temp -> next;
	}
	return ret ? tmp : NULL;
}

int main () {
  printf ("\t Program to find the loop in linked list \n");
  printf ("\t *************************************** \n");
  add ( 11 );
  add ( 12 );
  add ( 13 );
  add ( 14 );
  printf ( "Display=============\n" );
  display ();
  printf ( "Makeloop=============\n" );
  makeloop ( Lptr );
  printf ( "Findloop=============\n" );
  printf ( findloop (Lptr) ? "Loop present\n" : "Loop absent\n" );
  display ();
  return 2;
}

