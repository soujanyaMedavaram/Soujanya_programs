#include<stdio.h>
# include <stdlib.h>
#include<string.h>
#include "aqueue.h"

#define NITEMS 50

AQUEUE *aqd;
main()
{
	char *line;
	aqd = openQa (NITEMS, 50 * sizeof(char *));
	line = malloc(50);
   	if (aqd == NULL) exit(1);
	while(1)
	{
		printf("Use E to exit, N<name> to Enq,  p to Deq and\n");
		fgets ( line, 50, stdin );
		//for ( line; isblank(*line); line++ );
		switch(*line)
		{
			case 'N':
				if (aQfull(aqd)) continue;
				enQa(aqd, (char *)&line[1],strlen(line));
				break;

		 	case 'p': case 'P':
				if (aQempty(aqd)) {
					printf ("\nqueue is empty\n");
					break;
				}
				deQa(aqd, (char *)&line);
				printf("%s\n",line);
				break;
			case 'e': case 'E':	
				while (!aQempty(aqd))
				{
					deQa(aqd,(char *)&line);
					printf("%s\n",line);
				}exit(0);
		}
	}
}
