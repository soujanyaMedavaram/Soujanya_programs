# include <stdio.h>
char * malloc (int);
char * realloc (char *, int);
void print_para (char ***);
void print_sent (char **);
void print_word (char *);

main()
{
	int c;
	char ***para;
	int sentance_begins;
	int word_begins;
	int nos;
	int now;
	int pos;
	int white;

	para = NULL;
	word_begins = 1;
	nos = 0;
	now = 0;
	pos = 0;
	while ((c = getchar() ) != EOF)
	{
		if ( c == ' ' || c == '\t' || c == '\n') white = 1;
		else white = 0;
		if (!white && sentance_begins)
		{
			sentance_begins = 0;
			para = (char ***)realloc ((char *)para,(++nos + 1) * sizeof(*para));
			para[nos - 1] = NULL;
			para[nos] = NULL;
			now = 0;
		}
		if (!white && word_begins)
		{
			word_begins = 0;
			para[nos - 1] = (char **)realloc((char *)para[nos - 1],(++now + 1) *
			sizeof(**para));
			para[nos - 1][now] = NULL;
			pos = 0;
		}
		if (white) word_begins = 1;
		else if ( c == '.') sentance_begins = 1;
		else
		{
			para[nos - 1][now - 1] = realloc(para[nos - 1][now - 1], (++pos + 1)
			* sizeof(***para));
			para[nos - 1][now - 1][pos - 1] = c;
			para[nos - 1][now - 1][pos - 1] = '\0';
		}
	}
	print_para(para);
}

void print_para(char ***para)
{
	if (!para) return;
	while (*para)
	{
		print_sent(*para++);
		putchar('.');
		if (*para) putchar (' ');
	}
	putchar ('\n');
}

void print_sent(char **sent)
{
	if (!sent) return;
	while (*sent)
	{
		print_word(*sent++);
		if (*sent) putchar(' ');
	}
}
void print_word(char *word)
{
	if (!word) return;
	while (*word) putchar (*word++);
}
