# include <stdio.h>
# include "queue_list.h"

# define	NITEMS	5

char line[100];
main ( )
{
	int num;
	register L_QUEUE *qld;
	register char *p;
	qld = (L_QUEUE *)lopen_queue ( NITEMS, sizeof(num) );
	if ( qld == NULL ) {
		fprintf (stderr, "memory not allocated\n");
		exit ( 1 );
	}
	while ( 1 ) {
		printf ( "\n E to exit;P to deQ; Num to enQ:");
		fgets ( line, 100, stdin );
		for ( p = line; *p ==  ' ' || *p == '\t'; p++ );
		switch ( *p ) {
			case '0': case '1': case '2': case '3': case '4': 
			case '5': case '6': case '7': case '8': case '9':
		 		if ( QL_Full(qld) ) {
					printf ( "\n queue is full\n");
					break;
				}
				num = atoi(p);
				enQ ( qld, (char *)&num);
				break;
			case 'p':
				if ( QL_Empty(qld) ) {
					printf ( "\n queue is empty\n");
					break;
				}
				deQ ( qld, (char *)&num );
				printf ( "%d\n", num );
				break;
			case 'e':
				while ( !QL_Empty(qld) )
				{
					deQ ( qld, (char *)&num );
					printf ( "%d\n", num);
				}
				exit ( 0 );
		}
	}
	close_que ( qld );
	exit ( 0 );
}
