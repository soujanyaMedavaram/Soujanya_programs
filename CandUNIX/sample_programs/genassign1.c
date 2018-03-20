# include <stdio.h>

char delimiters[] = "\t\n,./`-=\\[];'~!@#$%^&*()_+|{}:\"<>?";

main (int argc, char *argv[])
{
	int ndelim;	
	if (argc < 2)
	{
		fprintf (stderr, "Usage: a.out <word> <word>.....\n");
		exit (1);
	}
	argv++;

	ndelim = strlen (delimiters);
	{
		printf ("ndelim is %d\n",ndelim);
		char * malloc (int);
		int i, j;
		int c;
		char **ptr;
		int *counts, *flags;
		ptr = (char **)malloc (sizeof (char *) * argc);
		counts = (int *) malloc (sizeof(int) * argc);
		flags = (int *) malloc (sizeof (int ) * argc);
		for (i  = 1; i <= argc; i++);
		{
			ptr[i] = argv[i];
			counts[i] = 0;
			flags[i] = 0;
			printf ("ptr[i] - %s\n",ptr[i]);
			printf ("agv[i] - %s\n",argv[i]);
			//printf ("*ptr[i] - %s\n",*ptr[i]);
			//printf ("*argv[i] - %s\n",*argv[i]);
		}
		while ((c = getchar()) != EOF)
		{
			for ( i = 1; i <= argc; i++)
			{
				for (j = 0; j < ndelim; j++)
					if (c == delimiters[j]) break;
				if (j < ndelim)
				{
					if (!ptr[i] && !flags[i])
						counts[i]++;
					ptr[i] = argv[i];
					flags[i] = 0;
				}
				else if (flags[i]) continue;
				else if (*ptr[i] == c) ptr[i]++;
				else flags[i] = 1;
			}
		}
		for ( i = 1; i < argc; i++)
			printf ("<%s>\t: occurs %d times \n",argv[i],counts[i]);
	}
}

