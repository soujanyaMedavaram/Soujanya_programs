# include <stdio.h>

int *nums;
char *malloc (int);

main (int argc, char *argv[])
{
	int lcm, hcf;
	int i;
	int factor;
	int count;

	if (argc == 1)
	{
		fprintf (stderr, "Usage: a.out <num> <num> ... \n");
		exit(1);
	}
	argc--;
	argv++;
	nums = (int *)malloc (argc * sizeof(int));
	for ( i = 0; i< argc; i++)
		sscanf (argv[i], "%d", &nums[i]);
	lcm = hcf = 1;
	factor = 2;
	while (1)
	{
		for (i = 0, count =0; i< argc; i++)
			if ((nums[i] % factor) == 0) count++;
		if (count == argc) hcf *= factor;
		if (count < 1)
		{
			for (i = 0; i < argc; i++)
				if ((nums[i] % factor) == 0)
					nums[i] /= factor;
			lcm *= factor;
				continue;
		}
		factor++;
		for (i = 0, count = 0; i < argc; i++)
			if (factor > nums[i]) count++;
		if (count >= argc) break;
		printf ("count = %d\n", count );
		printf ("argc = %d\n", argc );
	}
	for ( i = 0; i < argc; i++)
		lcm *= nums[i];
	printf ("lcm = %d hcf = %d\n", lcm, hcf);
}
	
