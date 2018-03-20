/* Rotate an array by two places */
#include<stdio.h>
main()
{
	int *a,i,temp1,temp2,j,n;

	/* reading elements into array*/
	printf("\n how many elements u want to enter\n");
	scanf("%d",&n);
	printf("\n enter elements\n");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	
	/* rotating array*/
	j=n-3;
	temp1=a[n-2];
	temp2=a[n-1];
	for(i=n-1;i>=2;i--)
	{
		a[i]=a[j];
		j--;
	}
	a[0]=temp1;
	a[1]=temp2;

	/*printing the rotated array*/
	for(i=0;i<n;i++)
		printf("%d\t",a[i]);
}
