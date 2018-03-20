# include <stdio.h>
# include <math.h>

# define MAXOP	100
# define NUMBER '0'

int getop(char []);
void push(double);
double pop ();

int sp = 0;
double val[MAXOP];

main()
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop()- op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("ERROR: Zero divisior\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0)
					push(pop() / op2);
				else
					printf("ERROR: Zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n",pop());
				break;
			default:
				printf ("Error: unknown command %s\n",s);
				break;
		}
	}
	return 0;
}

void push(double f)
{
	if (sp < MAXOP)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %lf\n",f);
}

double pop()
{
	if (sp > 0) 
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}
