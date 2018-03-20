# include <stdio.h>
# define ROQ	10
# define Size	dd->size
# define Data	dd->data
# define Nitems	dd->nitems
# define Temp	dd->temp
# define Temp2	dd->temp2
# define Temp3	dd->temp3
# define Walk	dd->walk
# define Swap	dd->swap
typedef struct items ITEM;
ITEM *dd;

struct items
{
	int size;
	int nitems;
	char *data;
	char *temp, *temp2, *temp3, *walk, *swap;
};

struct items *open(struct items *dd,int size)
{
	dd = (ITEM *)malloc(ROQ * sizeof(char));
	dd->size = size;
	Nitems = 0;
	return dd;
}
void insert(char *data)
{
	int flag = 1, i = 1;
	if(flag == 1)
		memcpy(Temp,data,Size);
	if (!(Nitems % 10))
		dd = (ITEM *)realloc(dd,++i * ROQ * sizeof(char));
	memcpy(Data,data,Size);
	Data += Size;
	Nitems++;
}
	
void sort()
{
	int i, j, x;
	Temp2 = Temp;
	Temp3 =Temp + Size;
	for ( i = 0; i < Nitems; i++)	
	{
		for ( j = i; j < Nitems; j++)
		{
			Temp3 = Temp2 + Size;
			x = memcmp(Temp2,Temp3,Size);
			if (x > 0)
			{
				Swap = Temp2;
				Temp2 = Temp3;
				Temp3 = Swap;
			}
			Temp3 += Size;
		}
		Temp2 += Size;
	}
}

void print()
{
	Walk = Temp;
	int i;
	for ( i = 0; i < Nitems; i++)
	{
		printf("%s\n",*Walk);
		Walk += Size;
	}
}

main()
{
	char *input;
	int i = 1;
	struct items *dd;
	dd = open(dd,sizeof(char));
	printf("enter the input to sort\n");
	while(1)
	{	
		fgets(input,50,stdin);
		insert(input);
	}
	sort();
	print();
}
	
	
