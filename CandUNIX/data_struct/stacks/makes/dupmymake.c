# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

void read_file ( FILE *fp );
char *get_word ( char *);
char *get_line ( FILE *fp );

typedef struct Node NODE;
struct Node {
	char *target;
	NODE **depend;
	char ***commd;
};

static int cl, cw, ndcou;
static int cpara, cline;
static nod, all;

NODE *nd = NULL;
NODE **all_targ = NULL;
void p_str ( ) {
	int i;
	for ( i = 0; i < nod; i++ ){
		printf ( "target: %s\n", nd[i].target);
	}
}

main ( int argc, char *argv[] ) {
	FILE *fp;
	int file_found = 0, n = 0, i;
	char **usr_target = NULL;

	while ( *++argv ) {
		if ( strcmp ( *argv, "-f" ) == 0 ) {
			file_found = 1;
			*++argv;
			if ( (fp = fopen ( *argv, "r" )) == NULL ) {
				fprintf ( stderr, "%s : file not opened\n" , *argv);
				continue;
			}
			read_file ( fp );
			fclose ( fp );
		} else { 
			usr_target = realloc ( usr_target, (n+2) * sizeof ( char * ) );
			usr_target[n++] = strdup ( *argv );
		}
	}
	if ( file_found == 0 ) {
		if ( (fp = fopen ( "makefile", "r" )) == NULL ) {
			fprintf ( stderr, " NO file to open \n" );
			exit ( 1 );
		}
		read_file ( fp );
		fclose ( fp );
	}
	//  still mymake 
}

void read_file ( FILE *fp ) {
	char *line, *word;

	cpara = cline = ndcou = nod = all = 1;
	cl = cw = 0;
	while ( (line = get_line ( fp ) ) != NULL ) {
		switch ( *line ) {
			case '\t': case '#': case '\n':
				while ( isblank(*line) != 0 ) line++;
				if ( *line == '#' || *line == '\n' )
					continue;

				// store the rest 'line' into ***cmds

				nd[ndcou - 2].commd = realloc ( nd[ndcou - 2].commd, \
				(cpara+2) * sizeof ( char * ));
				cpara++;
				while ( (word = get_word(line)) != NULL ){
					nd[ndcou - 2].commd[cl] = realloc(nd[ndcou - 2].\
					commd[cl], (cline+2) * sizeof(char *) );
					nd[ndcou -2].commd[cl][cw] = strdup(word);
					cl++,cw++;
				}
				nd[ndcou -1].commd[cl] = NULL;
				break;

			default:
				while ( isblank(*line) != 0 ) line++;
				if ( *line == '\n' ) continue;
				if ( strchr(line, ':' ) == NULL ) {
					fprintf ( stderr, "No target found\n" );
					return;
				} else {
					nd = realloc ( nd, (ndcou)*sizeof(NODE) );
					all_targ = realloc(all_targ, (all + 1)*sizeof(NODE *));
					all_targ[all - 1] = (NODE *)strdup((char *)nd);
					nd[ndcou - 1].target = NULL;
					nd[ndcou - 1].depend = NULL;
					nd[ndcou - 1].commd = NULL;
					ndcou++;	
				}

				//store in to **target

				while ( (word = get_word(line)) != NULL ) {
					if ( strcmp(word, ":") == 0 ) break;
					nd[ndcou - 2].target = strdup(word);
				}
				nd[ndcou - 2].target = NULL;
				line++;
				while ( isblank(*line) != 0) line++;

				//store into **depend

				while ( (word = get_word(line)) != NULL ) {
					nd[ndcou - 2].depend = realloc ( nd[ndcou -2].depend,\
					nod  * sizeof(NODE *) );
					nd[ndcou -2].depend[nod-1] = (NODE *)strdup(word);
					nod++;
				}
				nd[ndcou - 2].depend[nod] = NULL;
				break;
		}
	}
}

char * get_word ( char *line ) {
	char *word;
	word = malloc ( 25 );
	if ( *line = ':' ) {
		strcpy ( word, ":" );
		return word;
	}
	while ( *line != ' ' && *line != '\t' && *line != '\0' ) 
			*word++ = *line++;
	*word = '\0';
	return word;
}
	

# define LEN 2 
char * get_line ( FILE *fp ) {
	static char *line = NULL;
	static int len =0;
	int offset;
	if ( fp == NULL ) {
		free ( line );
		return NULL;
	}
	if ( !len ) line = malloc ( len = LEN );
	offset = 0;
	while ( 1 ) {
		if ( fgets ( line + offset, len - offset, fp ) == NULL ) {
			if ( offset ) return line;
			else return NULL;
		}
		if ( line[strlen(line) - 1] != '\n' )
			line = realloc ( line, len += LEN );
		else {
			line[strlen(line) - 1] = '\0' ;
			if ( line[strlen(line) - 1] != '\\' ) 
				return line;
			line[strlen(line) - 1 ] = ' ' ;
		}
		offset = strlen(line);
	}
}

