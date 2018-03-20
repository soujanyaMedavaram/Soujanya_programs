# include<stdio.h>
# include"queuec.h"

char line[100];
QUEUE *qd;

main()
{
	int num;
	register char *p;
	qd = openQ(sizeof(num));
	if (qd == Q_FAIL) exit(1);
	while (1)
	{
		printf("Use E to exit, P to pop, Number to push:");
		if (fgets (line,100,stdin) == NULL)
			exit(2);
		for (p = line; *p == ' ' || *p == '\t';p++);
		switch(*p)
		{
			case '0':case '1':case '2':case '3': case '4':
			case '5':case '6':case '7':case '8': case '9':
					num = atoi(p);
				enQ (qd, (char *)&num);
				break;

			case 'p': case 'P':
				if (Qempty(qd)) break;
				deQ (qd, (char *)&num);
				printf ("%d\n",num);
				break;

			case 'e': case 'E':
				while ( !Qempty(qd) )
				{
					deQ (qd,(char *)&num);
					printf("%d\n",num);
				}
				closeQ ( qd );
				exit(0);
		}
	}
}
