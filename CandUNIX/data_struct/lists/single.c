#include<stdio.h>
struct list
{
	int data;
	struct list *link;
};
main()
{
	typedef struct list *node,*head,*temp,*head1;
	char c='y';
	head=(list *)malloc(sizeof(list));
	head1=head;
	printf("\n enter element\n");
	scnaf("%d",&head->data);
	head->link=NULL;
	while(c=='y')
	{
	
		printf("\n do u want to enter anpther lement\n");
		scnaf("%c",&c);
		if(c=='y')
		{
			node=(list *)malloc(sizeof(list);
			printf("\n enter the element\n");
			scnaf("%d",&node->data);
			temp=node;
			head->next=node;
			head=temp;
		}
	}
	for(temp=head1;temp!=NULL;temp=temp->next)
	 	printf("%d",temp->data);
}
