#include<stdio.h>
# include <stdlib.h>
#include "aqueue.h"

#define NITEMS 50

char line[100];
AQUEUE *aqd;
main() {
	int count = 0;
	struct Int {
		char type;
		int value;
	}i1;
	struct Double {
		char type;
		double value;
	}d1;
	union item {
		char type;
		struct Int Int;
		struct Double Double;
	};
	union item item;
	register char *p, *temp;
	aqd = openQa (NITEMS, sizeof(item));
   	if (aqd == NULL) exit(1);
	while(1) {
		printf("Use E to exit, num to Enq,  p to Deq and\n");
		fgets(line,100,stdin);
		count = 0;
		for ( p = line; *p == ' ' || *p == '\t'; p++);
		switch ( *p ) {
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': case '.':
			temp = p;
			while (*temp != '\0') {
				if (*temp == '.') {
				    count = 1;  	
					item.Double.value = atof(p);
					item.type = 'D';
					if (aQfull(aqd)) continue;
					if(!enQa(aqd, (char *)&item,sizeof(item)))
					break;
				}
				temp++;
			}
			if (count == 0) {
				item.Int.value = atol(p);
				item.type = 'L'; 
				if (aQfull(aqd)) continue;
				if(!enQa(aqd, (char *)&item, sizeof(item)));
			}
			break;

		case  'p' : case 'P' :
			if (aQempty(aqd)) {
				printf ("\n queue is empty\n");
				continue;
			}
			deQa(aqd, (char *)&item);
			if (item.type == 'D')
				printf("%lf\n",item.Double.value);
			else if (item.type == 'L')
				printf("%d\n",item.Int.value);
			break;
		case  'e'  : case 'E' : 
			while (!aQempty(aqd)){
				deQa(aqd,(char *)&item);
				if (item.type == 'D')
					printf("%lf\n",item.Double.value);
				else if (item.type == 'L' )
					printf("%d\n",item.Int.value);
			}exit(0);
		}
	}
}
