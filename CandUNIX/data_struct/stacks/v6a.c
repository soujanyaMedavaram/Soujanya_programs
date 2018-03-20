#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

#define NITEMS 50

char line[100];
STACK *sd;

main()
{
	double num;
	register char *p;
	sd = stack_open(NITEMS,sizeof(num));
	if (sd == S_FAIL) exit(1);
	while(1)
	{
		printf("USe E to exit; P to pop; Number to push:");
		if (fgets(line,100,stdin) == NULL)
			exit(2);
		for(p = line; *p == ' ' || *p == '\t'; p++);
		switch(*p)
		{
			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9': case '.' :
				if (stack_full(sd)) continue;
				num = atof(p);
				push (sd,(char *)&num);
				break;
			case 'p':case 'P':
				if(stack_empty(sd)) break;
				pop (sd,(char *)&num);
				printf("%6.2lf\n",num);
				break;
				case 'e':case 'E':
					while(!stack_empty(sd))
					{
						pop (sd,(char *)&num);
						printf("%6.2lf\n",num);
					}
					exit(0);
		}
	}
}
