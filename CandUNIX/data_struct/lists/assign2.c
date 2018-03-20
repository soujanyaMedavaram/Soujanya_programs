#include<stdio.h>
#include<string.h>

main()
{
	char **name, **name2,**first,ch;
	char *line, *temp;
	int count = 0,n = 1, flag = 0;
	int i, j;
	while(1)
	{
		printf("\n enterE to enter word\n \
		D to delete R for reportQ to quit\n"); 
		scanf(" %c",&ch);	
		line = (char *)malloc(50);
		temp = (char *)malloc(50);
		switch(ch)
		{
			case 'E':
				printf("\n enter no. of names\n");
				scanf("%d",&n);
				name = (char **)malloc(50 * n);
				if (name == NULL)
					printf("memory can't be allocated\n");
				for (i = 0; i < n; i++)
				{
					printf("\n enter word\n");
					scanf("%s",line);
					printf("the line is %s \n",line);
					if (count == 0)
					{
						*name = line;
						printf ("the name is %s\n",*name);
						printf ("the line is %s\n",line);
						count++;
						first = name;
						*name++;
					}
					else 
					{
					printf ("the name is %s\n",*name);
					while( (strcmp(*name,line) > 0) && *name)
					{
						printf ("the name is %s",*name);
						printf ("the line is %s", line);
						//*name = (char *)malloc(50);
						temp = *name;
						*name = line;
						line = temp;
						*name++;
					}}
					//if (*name) *name = line;
					name = first;
				}
				//*name = (char *)realloc(name,n * (50 * sizeof(char)));
				break;

			case 'D':

				printf("\n enter element to delete\n");
				scanf("%s",line);
				for ( i = 1; i < n; i++)
				{
					if (strcmp(name[i], line) == 0)
					{
						for ( j = i; j < (n-1); j++)
							strcpy(name[j],name[j + 1]);
						flag++;
						n--;
					}
				}
				if (n == 1)
					count = 0;
				if (flag == 0)
					printf("\n element not found\n");
				break;

			case 'Q':
				exit(0);

			case 'R':
				name = first;	
				for( i = 0; i < n ; i++)
					printf("%s\n",*name++);
				break;
		}
	}
}

				

			

