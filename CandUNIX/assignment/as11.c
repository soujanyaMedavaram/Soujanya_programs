# include <stdio.h>
# include <stdlib.h>
# include <string.h>

main()
{
	float f_arr[50],tempf;
	char str[50], tempstr[40],words[50][40];
	int i_arr[50], temp;
	int c , row, col,i, j, k;
	int f_flag, i_flag, s_flag;
	row = col = f_flag = i_flag = s_flag = k = 0;
	while( ( str = gets()) != EOF)
	{
		for ( i = 0; i <strlen(str); i++)
		{
			if(str[i] >= '0' && str[i] <= '9')
				i_flag = 1;
			else
				i_flag = 0;
		}
		for ( i = 0 ; i < strlen(str); i++)
		{
			if((str[i] >= '0' && str[i] <= '9')|| str[i] == '.')
				f_flag = 1;
			else 
				f_flag = 0;
		}
		for ( i = 0; i < strlen(str); i++)
		{
			if(str[i] >= 'a' && str[i] <= 'z')
				s_flag = 1;
			else 
				s_flag = 0;
		}
		if(f_flag == 1 || sfalg == 1)
			i_flag = 0;
		if(i_falg == 1)
			i_arr[k] = atoi(str);
		else if (f_flag == 1)
			i_arr[k++] = atof(str);
		else if (s_flag == 1)
			words[k++] = str;
	}
		if(i_flag == 1 && f_flag == 1 && s_flag == 1)
		{
			printf("\n undefined data\n");
			exit(2);
		}
	printf ("\n fflag = %d\tsflag = %d\t iflag = %d\n",f_flag,s_flag,i_flag);
	for ( i = 0; i < row; i++)
		printf ("%s\n",str[i]);
	if (f_flag == 1)
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
			printf("%d\n",f_arr[i]);
	}

	if (s_flag == 1)
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

