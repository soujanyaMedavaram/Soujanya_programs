main ()
{
int i, j= 10;
for ( i =0; i < 9; i++){
		static int j = 3;
		j++;
		printf ("%d",j);
}
printf ("%d",j);
}
