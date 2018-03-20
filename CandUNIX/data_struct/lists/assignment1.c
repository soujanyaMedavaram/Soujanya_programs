#include <stdio.h>

main()
{
	int *nums, i, noe = 0, ele;
	int j, flag = 0, temp;
	char line[100], *p;
	nums = (int *)malloc(sizeof(int));
	while (1)
	{
		printf ("<num> to enter D<num> to delete R to report E to exit:"); 
		fgets(line, 100, stdin);
		for(p = line; *p == ' ' || *p == '\t';p++);
		switch (*p)
		{
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				ele = atoi(p);
				if (!noe)
					nums[noe] = ele;
				else
					for ( i = 0; i < noe; i++)
						if ((nums[i]) > ele)
						{
							temp = nums[i];
							nums[i] = ele;
							ele = temp;
						}
				nums[noe] = ele;
				noe++;
				printf ( "noe in num case = %d\n", noe );
				nums = (int *)realloc(nums, (noe + 1) * sizeof(int));
				break;

			case 'D': case 'd':
				p++;
				printf ( "noe = %d\n", noe );
				ele = atoi(p);
				printf ( "Check ele = %d\n", ele );
				flag = 0;
				for ( i = 0;i < noe; i++)
				{
					if (nums[i] == ele)
					{
						printf ( "The value is %d\n", nums[i] );
						flag++;
						for ( j = i; j < (noe - 1); j++)
							nums[j] = nums[j + 1];
						noe--;
						printf ( "**\n" );
						break;
					}
				}
				if ( flag == 0)
					printf ("\n Element not found in the list\n");
				break;	

			case 'R': case 'r':

				printf("\n elements in the list are \n");
				for ( i = 0; i < noe; i++)
					printf ("%d\t",nums[i]);
				printf ( "\n" );
				break;

			case 'E': case 'e':

				free (nums);
				exit (0);
			
			default: 

				printf("\n wrong choice\n");
				break;

		}
	}
}
