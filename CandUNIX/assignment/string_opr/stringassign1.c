#include<stdio.h>

#define WAITING_FOR_T_OR_A 0
#define GOT_T 1
#define GOT_TH 2
#define GOT_THE 3
#define GOT_A 4
#define GOT_AN 5
#define GOT_AND 6
#define GOT_WRONG 7
#define WHITE(c) ((c==' ')||(c=='\t')||(c=='\n'))

main()
{
	int the_count = 0, and_count = 0,c;
	int state = WAITING_FOR_T_OR_A;
	while((c=getchar())!=EOF)
	{
		switch(state)
		{
			case WAITING_FOR_T_OR_A:
				if( c == 't' )
					state = GOT_T;
				else if( c == 'a' )
					state = GOT_A;
				else if(WHITE(c))
					continue;
				else
					state = GOT_WRONG;
				break;

			case GOT_T:
				if( c == 'h')
					state = GOT_TH;
				else if(WHITE(c))
					state = WAITING_FOR_T_OR_A;
				else
					state = GOT_WRONG;
				break;

			case GOT_TH:
				if( c == 'e')
					state = GOT_THE;
				else if(WHITE(c))
					state = WAITING_FOR_T_OR_A;
				else
					state = GOT_WRONG;
				break;

			case GOT_THE:
				if(WHITE(c))
				{
					state = WAITING_FOR_T_OR_A;
					the_count++;
				}
				else
					state = GOT_WRONG;
				break;
		
			case GOT_A:
				if( c == 'n' )
					state = GOT_AN;
				else if(WHITE(c))
					state = WAITING_FOR_T_OR_A;
				else
					state = GOT_WRONG;
				break;

			case GOT_AN:
				if( c == 'd' )
					state = GOT_AND;
				else if(WHITE(c))
					state = WAITING_FOR_T_OR_A;
				else
					state = GOT_WRONG;
				break;

			case GOT_AND:
				if(WHITE(c))
				{
					state = WAITING_FOR_T_OR_A;
					and_count++;
				}
				else
					 state  = GOT_WRONG;
				break;

			case GOT_WRONG:
				 if(WHITE(c))
				 	state = WAITING_FOR_T_OR_A;
				break;
		}
	}
	printf("\n the number of occurences of word 'the' is %d",the_count);
	printf("\n the number of occurences of word 'and' is %d",and_count);
}
