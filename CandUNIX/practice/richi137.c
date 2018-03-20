# include <stdio.h>
# include <string.h>
# include <ctype.h>
# define MAXWORD	100

int getword ( char *, int );
struct key *binsearch ( char *, struct key *, int );

main () {
	char word[MAXWORD];
	struct key *p;
	
	while (getword (word, MAXWORD) != EOF )
		if (isalpha(word[0]))
			if ((p = binsearch(word,keytab,NKEYS)) != NULL )
				p->count++;
	for ( p = keytab; p < keytab + NKEYS; p++ )
		if (p->count > 0)
			printf ("%4d %s\n",p->count, p->word);
	return 0;
}

struct key *binsearch ( char *word, struct key *tab, int n);
{
	int cond;
	struct key *low;
	struct key *high;
	struct key *mid;

	low = tab;
	high = &tan[n];
	while (low <= mid ) {
		mid = low + (high - low) / 2 ;
		if ( (cond = strcmp(word,mid->word)) < 0 )
			high = mid;
		else if (cond > 0 )
			low = mid;
		else 
			return mid;
	}
	return NULL;
}
