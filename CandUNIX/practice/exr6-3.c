# include <stdio.h>
# include <string.h>
# include <stdlib.h>


int word_count;
void insert_word ( char [], int );
void sort_result ( );
void cross_referencer(FILE *, FILE *);
int noise_wrod ( char temp_word[] );
void print_result ( );

main ( int argc, char *argv[] ) {
	FILE *in, *out;
	in = stdin;
	out = stdout;
	int flag = 0;
	word_count = 0;
	
	if ( argc == 1 ) {
		cross_referencer(stdin, stdout);
		exit ( 1 );
	}
	while ( *++argv ) {
		if ( !strcmp (*argv, "-") ) {
			in = stdin;
			flag = 1;
			continue;
		} else if (flag == 0)
		out = fopen (argv[1], "w");
		if ( flag == 1 ) {
			in = fopen (*argv, "r");
		}
		flag = 1;
		cross_referencer(in, out);
	}
	exit ( 0 );
}

char *noise[] = { "the", "a", "and", "this", "that", "is", "was", "in", "of",
					"on", "for", "to", "it", "if" };
				
# define NNOISE		( sizeof(noise) / sizeof(char *) )
struct detail {
	char *word;
	int count;
	int *line_nos;
} *details;

# define ROQ	10
void cross_referencer ( FILE *in, FILE *out ) {
	int c, i = 0;
	static lineno = 0;
	char temp_word[250];

	details = ( struct detail * )malloc ( ROQ * sizeof ( *details ) );
	printf ("\n enter the text\n" );
	while ( (c = getc(in)) != EOF ) {
		if ( c == '\n' || c== '\t' || c == ' ' ) { 
			if (c == '\n')	lineno++;
			temp_word[i] = '\0';
			i = 0;
			if ( !noise_word ( temp_word ) )
				insert_word ( temp_word, lineno );
		}
		else temp_word[i++] = c;
	}
	printf ("\n text entered\n");
	print_result ( );
}

int noise_word(char temp_word[]) {
	int i;
	for ( i = 0; i < NNOISE; i++ )
		if ( !strcmp ( temp_word, noise[i] ) ) return 1;
	return 0 ;
}


void insert_word ( char temp_word[], int lineno ) {
	int m = 1, i ;
	static j = 0;
	word_count++;
	if ( ! ( word_count % ROQ) )
		details = ( struct detail *) realloc ((char *)details, m++ * ROQ * sizeof(*details) );
		for ( i = 0; i < word_count - 1; i++ )
			details[i].count = 1;
		for ( i = 0; i < word_count-1; i++ ) 
			if ( !strcmp ( details[i].word, temp_word ) ) {
				details[i].count++;
				details[i].line_nos = (int *)malloc ( sizeof (int ) );
				details[i].line_nos[j++] = lineno;
				return;
			}
		details[i].word = malloc ( strlen ( temp_word ) );
		strcpy ( details[i].word, temp_word );
		details[i].line_nos =  ( int * )malloc ( sizeof ( int ) );
		details[i].line_nos[j++] = lineno;
}

/*void sort_result ( )
{
	struct detail *temp;
	int i, j;
	printf ("\n in function sort_result\n");
	for ( i = 0; i < word_count; i++ )
		for ( j = i + 1 ; i < word_count; i++)
			if ( strcmp ( details[i].word, details[j].word ) > 0 )
				temp = details[i];
				details[i] = details[j];
				details[j] = temp;
}*/

void print_result ( )
{
	int i, j;
	for ( i = 0; i < word_count; i++ ) {
		printf ("\n %s\t%d\t",details[i].word, details[i].count );
		for ( j = 0 ; j < details[i].count; j++ ) {
			printf ( "%d ",details[i].line_nos[j] );
		}
	}
}
