#include<stdio.h>
#include"stack.h"

#define NITEMS 50

char line[100];
STACK *sd;

main()
{
	int num;
	register char *p;
	sd = stack_open(NITEMS,sizeof(num));
	if (sd == S_FAIL) exit(1);
	while(1)
	{
		printf("Use E to exit; P to pop; Number to push:");
		if (fgets(line,100,stdin) == NULL)
			exit(2);
		for(p = line; *p == ' ' || *p == '\t'; p++);
		switch(*p)
		{
			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9':
				if (stack_full(sd)) continue;
				num = atoi(p);
				push (sd,(char *)&num);
				break;
			case 'p':case 'P':
				if(stack_empty(sd)) break;
				pop (sd,(char *)&num);
				printf("%d\n",num);
				break;
			case 'e':case 'E':
				if ( stack_transient (sd) )
					while(!stack_empty(sd))
					{
						pop (sd,(char *)&num);
						printf("%d\n",num);
					}
				close_stack(sd);
				exit(0);
		}
	}
}
