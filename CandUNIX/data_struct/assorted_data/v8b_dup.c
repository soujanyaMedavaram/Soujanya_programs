#include<stdio.h>
# include <stdlib.h>
#include<string.h>
#include "aqueue.h"

#define NITEMS 50

struct data {
	char *name;
};
struct data data;
AQUEUE *aqd;
main()
{
	char line[50], *p;
	aqd = openQa (NITEMS, 50 * sizeof(char *));
   	if (aqd == NULL) exit(1);
	while(1)
	{
		printf("Use E to exit, N<name> to Enq,  p to Deq and\n");
		fgets ( line, 50, stdin );
		for ( p = line; isblank(*p); p++ );
		switch(*p)
		{
			case 'N':
				p++;
				if (aQfull(aqd)) continue;
				data.name = malloc ( strlen(p) + 1);
				strcpy ( data.name, p );
				enQa(aqd, (char *)&data,strlen(p));
				break;

		 	case 'p': case 'P':
				if (aQempty(aqd)) {
					printf ("\nqueue is empty\n");
					break;
				}
				deQa(aqd, (char *)&data);
				printf("%s\n",data.name);
				break;
			case 'e': case 'E':	
				while (!aQempty(aqd))
				{
					deQa(aqd,(char *)&data);
					printf("%s\n",data.name);
				}exit(0);
		}
	}
}
