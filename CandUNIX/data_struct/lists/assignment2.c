#include<stdio.h>
#include<string.h>

main()
{
	char **name;
	int nlines = 0,n,j,flag = 0;
	char *p,line[100],temp[100];
	name = (char **)malloc(sizeof(char *) * 50);
	while (1)
	{
		printf ("\n enter E<word>to enter D<word>to delete R for report\
		Q for exit\n");
	    if(	fgets(line,100,stdin) == NULL) exit(1);
		for ( p = line; *p == '\t' || *p == ' '; p++);
		switch(*p)
		{
			case 'E':
				p++;
				name[nlines] = (char *)malloc(sizeof(char *) );
				if (!nlines )
					strcpy(name[nlines], p);
				else
					for ( n = 0; n < nlines; n++)
					if (strcmp(name[n],p) > 0)
					{
						strcpy(temp , name[n]);
						strcpy(name[n] , p);
						strcpy(p , temp);
					}
				strcpy(name[nlines] , p);
				nlines++;
				break;

			case 'R': case 'r':
				for ( j = 0; j < nlines; j++)
					printf ("%s\n",name[j]);
				break;

			case 'D':
				flag = 0;
				p++;
				for ( n = 0; n < nlines; n++)
					if (strcmp(name[n],p) == 0)
					{
						flag++;
						printf ("\n %s deleted \n",name[n]);
						for ( j = n; j < nlines - 1; j++)
							strcpy(name[j],name[j + 1]);
						nlines--;
						break;
					}
				if (flag == 0)
					printf ("Element not found \n");
				break;
			case 'Q':
				exit(0);
		}
	}
}
					
					



