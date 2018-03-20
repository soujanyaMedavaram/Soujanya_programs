#include <stdio.h>

main()
{
	int *nums, i, n, ele;
	int j, flag = 0, temp,  count = 1;
	char ch;
	nums = (int *)malloc(sizeof(int));
	n = 1;
	nums[n] = 0;
	while (1)
	{
		printf ("\nMENU\n1.ENTER <num>\n2. Delete\n3.Report\n4.Exit\n");
		scanf(" %c",&ch);
		fflush(stdin);
		switch (ch)
		{
			case '1':

				printf("\n enter the element \n");
				scanf("%d",&ele);
				fflush(stdin);
				if (count == 1)
				{
					nums[1] = ele;
					count++;
				}
				for ( i = 1; i < n; i++)
				{
					if ((nums[i]) > ele)
					{
						temp = nums[i];
						nums[i] = ele;
						ele = temp;
					}
				}			
				nums[n] = ele;
				n++;
				nums = (int *)realloc(nums, (n + 1) * sizeof(int));
				break;

			case '2':
			
				printf ("\n enter element to delete\n");
				scanf("%d",&ele);
				for ( i = 0;i < n; i++)
				{
					if ((nums[i]) == ele)
					{
						flag++;
						for ( j = i; j < (n - 1); j++)
							nums[j] = nums[j + 1];
						n--;
						break;
					}
				}
				if (n == 1)
					count = 1;
				if ( flag == 0)
					printf ("\n Element not found in the list\n");
				break;	

			case '3':

				printf("\n elements in the list are \n");
				for ( i = 1; i < n; i++)
					printf ("%d\t",nums[i]);
				break;

			case '4':

				free (nums);
				exit (0);
		/*	default:
			    printf ("\n wrong choice \n");
				break; */

		}
	}
}
