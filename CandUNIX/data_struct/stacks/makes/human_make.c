# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>

void mymake ( FILE ** fd, char * target );
char * get_line ( FILE * fp );
char * get_word ( char *  );

main ( int argc, char *argv[] ) {
	char ** usr_tgt;  int nusr_tgts;
	FILE ** fp;  int nfp;
	int fflag, i, file_found;
	
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
	usr_tgt[nusr_tgts] = NULL;
	fp[nfp] = NULL;
	if ( usr_tgt[0] == NULL )
		mymake ( fp, usr_tgt[0] );
	for ( i = 0; usr_tgt[i]; i++ )
		mymake (fp, usr_tgt[i] );
	for ( i = 0; fp[i]; i++ )
		fclose ( fp[i]);
	for (i = 0; usr_tgt[i]; i++)
		free( usr_tgt[i] );
	free( usr_tgt);
	free( fp );
	exit ( 0 );
}

void mymake ( FILE ** fp, char * target) {
	int i, j, k, c,prev_c, arr_fp, tab, indx, at_d_rate, first_word;
	int tgt_found = 0,ntokens = 0;
	static first_target = 0, ndepends = 0;
	static char **depends;
	char *line, **commd;
	char *word;
	struct stat tgt_buf, dp_buf;

	if ( !target ) {
		line = get_line ( fp[0] );
		if ( line[0] == '\t' ) {
			fprintf ( stderr, " *** commands commence before first\
				target. Stop\n" );
			exit ( 1);
		}
		target = malloc ( sizeof(char * ) );
		word = get_word ( line );
		strcpy ( target, word );
		word = get_word ( NULL );
		if ( strcmp ( word, ":" ) != 0 ) {
			fprintf ( stderr, " **** missing seperator. Stop\n" );
			exit ( 2 );
		}
	rewind ( fp[0] );
	}

	tab = 0;
	for ( i = 0; fp[i]; i++ ) {
		while ( c = getc ( fp[i] ) ) {
			if ( c == ' ' && c != '\t' && c != '\n' ){
				word[j++] = c;
				continue;
			}
			word[j] = '\0';
			j = 0;
			if ( c == '\t' && prev_c == '\n' ) {
				tab = 1;
				arr_fp = ftell ( fp[i] );
			}
			if ( tgt_found == 2 ) {
				for (k = 0; k <= i; k++ )
					rewind ( fp[i] );
				depends = realloc ( depends, (ndepends + 2 ) *\
					sizeof ( char * ) );
				depends[ndepends++] = strdup ( word );
				depends[ndepends] = NULL;
				mymake ( fp, word );
			}
			if ( tgt_found == 1) { 
				if ( strcmp ( word, ":" ) != 0 && first_target == 0 ) {
					fprintf ( stderr, "\n ***No rule to make\n" );
					exit ( 1 );
				}
				else  {tgt_found = 2; continue;}
			}

			if ( strcmp ( word, target ) != 0 && tgt_found == 0)
				continue;
			else {
				tgt_found = 1;
				first_target++;
				continue;
			}
		}
	}

	if ( tgt_found != 2 ) {
		if ( access ( word, F_OK ) != 0 ) {
			fprintf ( stderr, " *** '%s' file not found\n", word );
			exit ( 1 );
		}
		return;
	}
	if ( tab == 1 ) {
		indx = ndepends -1;
		while ( indx >= 0 ) {
			if ( strcmp ( depends[indx], target ) == 0 ) 
				break;
			stat( target, &tgt_buf );
			if ( stat ( depends[indx], &dp_buf ) == -1 ) {
				fprintf ( stderr, "*** '%s' Dependancy does not exist \n",\
					depends[indx] );
				exit ( 2 );
			}
			if ( tgt_buf.st_mtime < dp_buf.st_mtime ) {
				fseek ( fp[i], arr_fp, SEEK_SET);
				label :
					line = get_line ( fp[i] ); 
					if ( line[0] != '\t' )
						break;
					first_word = 0;
					at_d_rate = 0;
					for ( k =0; k < ntokens; k++ )
						free ( commd[k] );
					free ( commd );
					ntokens = 0;
					while ( word = get_word ( line ) ) {
						line = NULL;
						if ( first_word == 0 ) {
							if ( word[0] == '@' )
								at_d_rate = 1;
						}
						first_word++;
						commd = realloc ( commd, (ntokens + 2 ) * \
							sizeof ( char * ) );
						commd[ntokens++] = strdup ( word );
					}
					commd[ntokens] = NULL;
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
								while ( *commd ) {
									printf ( "%s", *commd );
									commd++;
								}
							break;
					}
				wait ( 0 );
				arr_fp = ftell ( fp[i] );
				c = getc ( fp[i] );
				if ( c == '\t' )
					goto label;
				else fseek ( fp[i], arr_fp, SEEK_SET );
			}
			indx--;
		}
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

				




