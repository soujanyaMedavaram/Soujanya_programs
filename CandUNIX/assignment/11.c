# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main()
{
	float f_arr[50],tempf;
	char str[50][40], tempstr[40];
	int i_arr[50], temp;
	int c , row, col,i, j;
	int f_flag, i_flag, s_flag;
	row = col = f_flag = i_flag = s_flag = 0;
	while( ( c = getchar()) != EOF)
	{
		if(c != '\n' && c != ' ')
		{
			str[row][col++] = c;
			if (c == '.')
				f_flag = 1;
			else if (c >= 'a' && c <= 'z')
				s_flag = 1;
			else if(c >= '0' || c <= '9')
				i_flag = 1;
			else
			{
				fprintf(stderr,"\n enter correct input\n");
				exit(1);
			}
			if (i_flag == 1 && s_flag == 1 && f_flag == 1)
			{
				printf("\n undefined data\n");
				exit(2);
			}
		}
		else
		{
			str[row][col] = '\0';
			row++;
			col = 0;
		}
	}

	if (f_flag == 1 || s_flag == 1)
		i_flag = 0;
	if(i_flag == 1)
	{
		for (i = 0; i < row; i++)
			i_arr[i] = atoi(str[i]);
		for ( i = 0; i < row; i++)
		{
			for ( j = i+1; j < row ; j++)
			{
				if ( i_arr[i] > i_arr[j])
				{
					temp = i_arr[i];
					i_arr[i] = i_arr[j];
					i_arr[j] = temp;
				}
			}
		}
		printf("\n\n");
		for(i = 0; i < row; i++)
			printf("%d\n",i_arr[i]);
	}

	else if (f_flag == 1)
	{

		for (i = 0; i < row; i++)
			f_arr[i] = atof(str[i]);
		for ( i = 0; i < row; i++)
		{
			for ( j = i+1; j < row ; j++)
			{
				if ( f_arr[i] > f_arr[j])
				{
					tempf = f_arr[i];
					f_arr[i] = f_arr[j];
					f_arr[j] = tempf;
				}
			}
		}
		printf("\n\n");
		for(i = 0; i < row; i++)
			printf("%f\n",f_arr[i]);
	}

	else if (s_flag == 1)
	{
		for ( i = 0; i < row; i++)
		{
			for ( j = i+1; j < row ; j++)
			{
				if ( (strcmp(str[i] , str[j]) > 0))
				{
					strcpy(tempstr , str[i]);
					strcpy(str[i] , str[j]);
					strcpy(str[j] , tempstr);
				}
			}
		}
		printf("\n\n");

		for(i = 0; i < row; i++)
			printf("%s\n",str[i]);
	}
	exit(0);
}

