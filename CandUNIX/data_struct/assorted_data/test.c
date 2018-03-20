#include<stdio.h>
# include <stdlib.h>
#include "aqueue.h"

#define NITEMS 50

char line[100];
AQUEUE *aqd;
main()
{
	struct Int
	{
		char type;
		int value;
	}i1;
	struct Double 
	{
		char type;
		double value;
	}d1;
	union item
	{
		char type;
		struct Int Int;
		struct Double Double;
	};
	union item item;
	register char *p;
	aqd = openQa (NITEMS, sizeof(item));
   	if (aqd == NULL) exit(1);
	while(1)
	{
		printf("Use E to exit, num to Enq,  p to Deq and\n");
	    printf("s<num> for short,l<num> for long d<num> for double:");
		fgets(line,100,stdin);
		for ( p = line; *p == ' ' || *p == '\t'; p++);
		switch( *p )
		{
			case 's': case 'l':
				p++;
				item.Int.value = atol(p);
				item.type = 'L'; 
				if (aQfull(aqd)) continue;
				printf("\nsize fo item %d\n",sizeof(item));
				enQa(aqd, (char *)&item, sizeof(item));
				break;
			case 'd':
				p++;
				item.Double.value = atof(p);
				printf ( "item.Double.value = %f\n", item.Double.value );
				item.type = 'D';
				if (aQfull(aqd)) continue;
				printf("\nsizeof item %d\n",sizeof(item));
				enQa(aqd, (char *)&item,sizeof(item));
				break;
			case 'p':
				if (aQempty(aqd)) continue;
				deQa(aqd, (char *)&item);
				if (item.type == 'D')
					printf("%lf\n",item.Double.value);
				else if (item.type == 'L')
					printf("%d\n",item.Int.value);
				break;
			case 'e':
				while (!aQempty(aqd))
				{
					deQa(aqd,(char *)&item);
					if (item.type == 'D')
						printf("%lf\n",item.Double.value);
					else if (item.type == 'L' )
						printf("%d\n",item.Int.value);
				}exit(0);
		}
	}
}
