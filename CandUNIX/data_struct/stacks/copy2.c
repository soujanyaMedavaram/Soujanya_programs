# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>

void mymake ( FILE ** fp, char * target); 
//int mymake ( FILE ** fp, char * file );
	// returns 0 or +ve on running commands (exit code / signal number)
	// returns -1 if file is upto date
	// returns -2 if file is not a target but exists
	// returns -3 if file is not a target but does not exist
void exec_cmd ( char **commd, int ntokens , int at_d_rate); 
char * get_line ( FILE * fp );
char * get_word ( char *  );

main ( int argc, char *argv[] ) {
	char ** usr_tgt;  int nusr_tgts;
	FILE ** fp;  int nfp;
	int fflag, i, file_found;
	char *word, *line;
	
	file_found = 0;
	fp = malloc ( sizeof (FILE *) );
	nfp = 0;
	usr_tgt = malloc ( sizeof (char *) );
	nusr_tgts = 0;
	for ( fflag = 0; *++argv; ) {
		if ( strcmp(*argv, "-f") == 0 ) {
			fflag = 1;
			continue;
		}
		if ( fflag ) {
			file_found = 1;
			fflag = 0;
			fp[nfp] = fopen ( *argv, "r" );
			if ( fp[nfp] == NULL ) {
				fprintf ( stderr, "%s: file not opened\n", *argv );
				exit ( 2 );
			}
			fp = realloc (fp, (++nfp + 1) * sizeof ( FILE *));
			continue;
		}
		usr_tgt[nusr_tgts] = strdup(*argv);
		usr_tgt = realloc ( usr_tgt, (++nusr_tgts + 1) * sizeof ( char *) );
	}
	if ( fflag ) {
		fprintf ( stderr, "Usage: mymake [-f makefile ]...target...\n" );
		exit ( 1 );
	}
	if ( !file_found ) {
		fp[nfp] = fopen ( "makefile","r");
		if ( fp[nfp] == NULL ) {
			fprintf ( stderr, "make file not opened\n" );
			exit ( 4 );
		}
		fp = realloc (fp, (++nfp + 1) * sizeof ( FILE *));
	}
	fp[nfp] = NULL;
	if ( nusr_tgts == 0 ) {
		line = get_line ( fp[0] );
		if ( line[0] == '\t' ) {
			fprintf ( stderr, " *** commands commence before first\
				target. Stop\n" );
			exit ( 1);
		}
		word = get_word ( line );
		usr_tgt[nusr_tgts] = strdup ( word );
		usr_tgt = realloc ( usr_tgt, (++nusr_tgts + 1) * sizeof ( char * ) );
		word = get_word ( NULL );
		if ( strcmp ( word, ":" ) != 0 ) {
			fprintf ( stderr, " **** missing seperator. Stop\n" );
			exit ( 2 );
		}
		rewind ( fp[0] );
	}
	usr_tgt[nusr_tgts] = NULL;
	for ( i = 0; usr_tgt[i]; i++ ) {
		i = mymake (fp, usr_tgt[i] );
		if ( i >= 0 ) {
			if ( WIFEXITED (i) ) ;
		} else if ( i == -1 )
			fprintf ( stderr, "%s is up-to-date\n", usr_tgt[i] );
		else if ( i == 2 )
			 fprintf ( stderr, "Nothing to be done for %s\n", usr_tgt[i] );
		else fprintf ( stderr, "No Rule to make target %s.  stop.\n",
							usr_tgt[i] );
	}
	for ( i = 0; fp[i]; i++ )
		fclose ( fp[i]);
	for (i = 0; usr_tgt[i]; i++)
		free( usr_tgt[i] );
	free( usr_tgt);
	free( fp );
	exit ( 0 );
}

void mymake ( FILE ** fp, char * target) {
	int i, j, k, c, arr_fp, at_d_rate, first_word;
	int minus;
	int tgt_found = 0,ntokens = 0;
	static int first_target = 0;
	static int prev_c;
	int exec_commd = 0;
	char *line, **commd = NULL;
	char *word, *word2;
	static char *first_tgt;
	struct stat tgt_buf, dp_buf;

printf ( "<%s>->target\n", target );
	word = malloc ( 100 * sizeof (char) );
	stat ( target, &tgt_buf );
	if ( first_target == 0 )
		first_tgt = strdup ( target );
	j = 0;
	for ( i = 0; fp[i]; i++ ) {
		rewind ( fp[i] );
		while ( tkn = get_word (fp[i]) ) {
			if ( !strcmp (tkn, "\t" ) ) {
				next_line:
					get_line ( fp[i] );
					continue;
			}
			if ( strcmp ( tkn, target ) ) goto next_line;
			if ( strcmp (get_word (fp[i]), ":") ) goto next_line;
			break;
		}


		while ( (c = getc ( fp[i] )) != EOF ) {
			if ( c == '\t' && prev_c == '\n') {
				get_line ( fp[i] );
				prev_c = '\n';
				continue;
			}
			if ( c != ' ' && c != '\t' && c != '\n' && c != ':' ) {
				word[j++] = c;
				continue;
			}
			if ( c == ':' ) word[j++] = c;
			word[j] = '\0';
			j = 0;
			if ( strcmp ( word, target ) == 0 ) {
				tgt_found = 1;
				continue;
			}
			if ( tgt_found == 1 ) {
				if ( strcmp ( word ,":") == 0 ) {
					first_target++;
					break;
				}
				else if ( first_target == 0 ){
					fprintf ( stderr, "*** No Rule to make. Stop\n" );
					exit ( 5 );
				}
				else {
					tgt_found = 0;
					continue;
				}
			}
			prev_c = c;
		}
		if ( tgt_found != 1 ) {
			if ( access ( target, F_OK ) != 0 && \
				word[0] != '\0'&&word[0] != ':') {
				fprintf ( stderr, " *** '%s' file not found\n", word );
				exit ( 1 );
			}
			return;
		}
		j = 0;
		while ( (c = getc ( fp[i] )) != EOF ) {
			if ( c == '\t' && prev_c == '\n') {
				if ( (exec_commd == 0) && (strcmp ( first_tgt, target) == 0)) {
					fprintf ( stderr, "'%s' is up to date\n",target );
					exit ( 3 );
				}
				else if ( exec_commd == 1 ) {
					label :
						line = get_line ( fp[i] );
						prev_c = '\n';
						first_word = 0;
						at_d_rate = 0;
						ntokens = 0;
						minus = 0;
						while ( word2 = get_word ( line ) ) {
							first_word++;
							line = NULL;
							if ( first_word == 1 ) {
								while ( *word2 == '@' || *word2 == '-' ){
									if ( *word2 == '@' )
										at_d_rate = 1;
									else if ( *word2 == '-' )
										minus = 1;
									word2++;
								}
							}
							commd = realloc ( commd, (ntokens + 2 ) * \
								sizeof ( char * ) );
							commd[ntokens++] = strdup ( word2 );
						}
						commd[ntokens] = NULL;
						exec_cmd ( commd, ntokens, at_d_rate );
						wait ( (int *) 0 );
						for ( k = 0; k < ntokens; k++ )
							free (commd[k]);
						free (commd);
						commd = NULL;		// For next call to realloc
						arr_fp = ftell ( fp[i] );
						line = get_line ( fp[i] );
						fseek ( fp[i], arr_fp, SEEK_SET );
						if ( line[0] == '\t' )
							goto label;
						else return;
				}
			}
			if ( c != ' ' && c != '\t' && c != '\n' && c != ':' ){
				word[j++] = c;
				continue;
			}
			if ( isblank(c) && j == 0) continue;
			word[j] = '\0';
			printf ( "<%s>->word\n", word );
			j = 0;
			arr_fp = ftell ( fp[i] );
			if ( word[0] == '\0' || word[0] == ':') continue;
			mymake ( fp, word );
			fseek ( fp[i], arr_fp, SEEK_SET );
			if ( exec_commd ) continue;
			if ( word[0] != '\0' && word[0] != ':' &&
					stat ( word, &dp_buf ) == -1 ) {
				fprintf ( stderr, " *** NO rule make target '%s', needed by\
					'%s' \n", word, target );
				exit ( 2 );
			}
			if ( tgt_buf.st_mtime < dp_buf.st_mtime )
				exec_commd = 1;
			prev_c = c;
			continue;
		}
	}
}

void exec_cmd ( char **commd, int ntokens , int at_d_rate) {
	int k;
	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "failed at fork\n" );
			exit ( 3 );
		case 0:
			execvp ( *commd, commd );
			fprintf ( stderr, "failed at exec\n" );
			exit ( 4 );
		default:
			if ( at_d_rate == 0 )
				for ( k = 0; k < ntokens; k++ )
					printf ( "%s ", commd[k] );
			printf ( "\n" );
			break;
	}
}

char * get_line ( FILE *fp ) {
	static int len =0;
	static char *line;
	char *p;
	int offset;
# define LEN 2 

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
			if ( line[strlen(line) - 1] != '\\' ) {
				if ( line[0] != '\t' || line[0] == '\t') {
				p = line;
					while (isblank( *p ) ) p++;
					if ( *p == '#' || *p == '\n' || *p == '\0')
						get_line ( fp );
				}
				return line;
			}
			line[strlen(line) - 1 ] = ' ' ;
		}
		offset = strlen(line);
	}
}

char * get_word ( char * curr_line ) {
	static char * line;
	static char * word = NULL;
	static int len = 0;
	int k = 0;

	if ( curr_line != NULL )
		line = curr_line;
	if ( len <= strlen (line) )
		word = realloc ( word, strlen(line) + 1 );
	while ( isblank ( *line ) ) line++;
	if ( *line == '\0' || *line == '\n') return NULL;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}
