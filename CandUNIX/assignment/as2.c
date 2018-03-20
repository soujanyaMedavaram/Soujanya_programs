/* ROTATING THE SINGLE DIMENSION ARRAY */

#include<stdio.h>
main() 
{
	int array[10],n,i,j,rotate[10];
	
	/* reading the array size and elements*/
	printf("\n Enter num for size for the array:"); 
	scanf("%d",&n);
	printf("\n enter elements in to the array\n");
	for(i=0;i<n;i++)
	scanf("%d",&array[i]);
	for(i=0;i<n;i++)
	printf("%d",array[i]);

	/* Rotating the array */
	rotate[0] = array[n-2];
	rotate[1] = array[n-1];
	j = 0;
	for(i=2;i<n;i++)
		rotate[i] = array[j++];

	
	/* printig rotated array*/
	printf("\n the rotated array is\n");
	for(i=0;i<n;i++)
	printf("%d\t",rotate[i]);
}
