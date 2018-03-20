# include <stdio.h>
# define ROQ 	10

int *nums, n = 0, reverse = 0;
void read()
{
	int i = 1;
	printf("\n enter elements\n");
	nums = (int *)malloc(ROQ * sizeof(int));
	while(1)
	{
		if(scanf("%d",nums + n) != 1)
			break;
		n++;
		if( !(n % ROQ) )
			nums = (int *)realloc(nums,++i * ROQ * sizeof(int));
	}
}

void sort()
{
	int i, j, temp;
	for( i =  0; i < n; i++)
	{
		for( j = i+1; j < n-1; j++)
		{
			if(reverse == 1)
			{
				if(nums[i] < nums[j])
				{
					temp = nums[i];
					nums[i] = nums[j];
					nums[j] = temp;
				}
			}
			else if(reverse == 0)
			{
				if(nums[i] > nums[j])
				{
					temp = nums[i];
					nums[i] = nums[j];
					nums[j] =temp;
				}
			}
		}
	}				
}

void print()
{
	int i;
	printf("\n the sorted list is \n");
	for( i = 0; i < n ; i++)
		printf("%d\n",nums[i]);
}
main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (*argv[1] == '-')
		{
			if(*++argv[1] == 'r')
				reverse = 1;
			else
			{
				fprintf(stderr,"Usage: a.out [-r] \n");
				exit(1);
			}
		}
	}
	read();
	sort();
	print();
	putchar('\n');
	exit(0);
}
