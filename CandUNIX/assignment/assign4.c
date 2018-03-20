#include<stdio.h>
#include<ctype.h>
#define SIZE 30
Rprint(char src[],char des[],int count)
{
	int i;
	for(i=0;i<count;i++)
		des[i]=src[i];
	des[i]='\0';
	printf("the string is: %s",des);
}
Lprint(char src[],char des[],int count)
{
	int i,j=0;
	i=strlen(src)-count;
	while(src[i]!='\0')
	{
		des[j]=src[i];
		j++;
		i++;
	}
	des[j]='\0';
	printf("\nthe string is: %s\n",des);
}
Mprint(char src[],char des[],int count,int position)
{
	int i,mid=position+count,j=0;
	for(i=position;i<mid;i++)
	{
		des[j]=src[i];
		j++;
	}
	des[j]='\0';
	printf("the string is %s:\n",des);
}
main()
{
	char src[SIZE],des[SIZE];
	int count,position,ch;
	printf("\n enter a string\n");
	scanf("%s",src);
	printf("\n enter the count of characters\n");
	scanf("%d",&count);
	while(1)
	{
		printf("\nMENU\n1.Rprint\n2.Lprint\n3.Mprint\n4.Exit\n");
		printf("enter your choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					Rprint(src,des,count);
					break;
			case 2: 
					Lprint(src,des,count);
					break;
			case 3: 
					printf("\n enter the position\n");
		 			scanf("%d",&position);
					Mprint(src,des,count,position);
					break;
			case 4: 
					exit(0);
			default:  
					printf("\n wrong input\n");
					exit(1);
		}
	}
}
