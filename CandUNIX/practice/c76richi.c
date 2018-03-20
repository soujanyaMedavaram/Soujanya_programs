# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# define MAXOP	100

void push(int);
int pop ();

int sp = 0;
int val[MAXOP];

main()
{
	char *line, *p;
	char c;
	int op2, temp;
	char s[MAXOP];

	line = malloc ( 100 );

	fgets(line,100,stdin);
	for( ;*line == ' ' || *line == '\t'; line++);
	while (*line != '\n')
	{
		switch (c = *line)
		{
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				push(atoi(&c));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				temp = pop();
				push(temp - op2);
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
			default :
				printf("error:unknown command %s \n",line);
				break;
		}
		line++;
	}
	printf("\n result is %d\n",pop() );
}

void push(int f)
{
	if (sp < MAXOP)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %d\n",f);
}

int pop()
{
	if (sp > 0) {
		printf ("val[--sp] = %d\n", val[sp -1] );
		return val[--sp];
	}
	else
	{
		printf("error: stack empty\n");
		return 0;
	}
}
