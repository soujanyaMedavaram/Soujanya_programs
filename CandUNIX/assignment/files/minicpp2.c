# include <stdio.h>
# include <string.h>
# include <errno.h>

void in_to_out (char *infile, FILE *out);
char *filename[100];
int ind = 0;

main(int argc, char *argv[])
{
	FILE *out;
	if (argc != 3)
	{
		fprintf (stderr,"Usage:a.out <input_file> <out_file>\n");
		exit(1);
	}
	
	if ( (out = fopen (argv[2] , "w")) == NULL ) {
		fprintf ( stderr, "Cant open the file : %s\n", argv[3] );
		exit ( 1 );
	}
	in_to_out (argv[1] , out);
	fclose ( out );
	exit(0);
}

void in_to_out (char *infile, FILE *fp2)
{
	FILE *fp;
	int i, dup_flag = 0;
	char s[50] , str[100];
	char *p;

	if ((fp = fopen (infile , "r")) == NULL)
		return ;
	while ( fgets ( str, 100, fp ) ) 
	{
		dup_flag = 0;
		strcpy(s , "/usr/include/");
		if ( strstr ( str, "include" ) ) 
		{
			if ( (p  = strchr ( str, '<' ) ) ) 
			{
				p++;
				*(strchr (p, '>')) = '\0';
				for ( i = 0; i < ind; i++)
				{
					if (!strcmp (filename[i] , p)) {
						dup_flag = 1;
						break;
					}
				}
				if (dup_flag != 1)
				{
					filename[ind++] = strdup(p);
					strcat ( s, p );
					in_to_out ( s, fp2 );
				}
			}
		}
		else
			fputs(str,fp2);
	}
	fclose (fp);
}
