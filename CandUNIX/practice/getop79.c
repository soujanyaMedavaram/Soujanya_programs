# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define NUMBER '0'

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int c,i;
	while ((s[0] = c= getch()) == ' ' || c == '\t');

	s[1] = '\0';
	i = 0;
	if (islower(c))
	{
		while (islower(s[++i] = c= getch()))
		;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		if (strlen(s) > 1)
			return NAME;
		else 
			return c;
	}

	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c)) 
		while(isdigit(s[++i] = c= getch()))
		;
	if (c == '.'){ 
	//	s[++i] = c;
		while (isdigit(s[++i] = c= getch()))
		;
	}
	s[i]  = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
# define BUFSIZE	100
char buf[BUFSIZE];
int bufp = 0;
int getch (void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch ( int c ) {
	if ( bufp >= BUFSIZE )
		printf ( "ungetch: too many characters \n" );
	else
		buf[bufp++] = c;
}

# define MAXOP	100

void push(int);
int pop ();

int sp = 0;
int val[MAXOP];

main()
{
	char *line, *p, *word;
	char c;
	int op2;
	char s[MAXOP];

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
				push(pop() - op2);
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
			default:
			printf ( "\n unknown command \n");
				break;
	}
}
return 0;
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
