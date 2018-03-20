/*prograam to convert 300,290,.....0 fahrenheit to celsius 
c=(5/9)(f-32)*/
#include<stdio.h>
main()
{
	double cels, fahr,upper=300,lower=0,step=10;
	printf("fahrenheit - celsius\n");
	for(fahr=upper;fahr>=lower;fahr=fahr-step)
	{
		cels=((5.0)/(9.0))*(fahr-32.0);
		printf("%lf - %lf\n",fahr,cels);
	}
}
