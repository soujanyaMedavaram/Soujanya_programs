# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>

void mymake ( FILE ** fd, char * target );
char * get_line ( FILE * fp );
char * get_word ( FILE * fp );

main ( int argc, char *argv[] ) {
	int * file_ptr, * file_cont;
	char ** usr_tgt;  int nusr_tgts;
	FILE ** fp;  int nfp;
	int fflag, i;

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
		fprintf ( stderr, "Usage: dasflj\n" );
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
	for ( i = 0; usr_tgt[i]; i++ )
		mymake (fp, usr_tgt[i] );
	for ( i = 0; fp[i]; i++ )
		fclose ( fp[i]);
	for (i = 0; i < usr_tgt[i]; i++)
		free( usr_tgt[i] );
	free( usr_tgt);
	free( fp );
	exit ( 0 );
}

void mymake ( FILE ** fp, char * target) {
	char ** depends;  int ndepends;
	char * line, * word;
	struct stat dpbuf, tgbuf;
	char *** commd = NULL; int ncmds; int ntokens;
	
	depends = malloc ( sizeof (char *) );
	ndepends = 0;
	commd = malloc ( sizeof (char *) );
	ncmds = 0;
	commd[ncmds] = malloc ( sizeof (char *) );
	ntokens = 0;
	for ( i = 0; fp[i]; i++ )
		rewind ( fp[i] );
	for ( i = 0; fp[i] && target = NULL; i++ ) {
		while ( line = get_line ( fp[i] )) {
			target = get_word ( line );
			word = get_word ( NULL );
			if ( strcmp ( word, ":" ) == 0 )
				break;
			else target = NULL;
		}
	}
	if ( target == NULL ) {
		fprintf ( stderr, "NO target found\n" );
		exit ( 1 );
	}
	for ( k = 0; k < i; k++ )
		rewind ( fp[i] );
	for ( i = 0; fp[i]; i++ ) {
		while ( line = get_line ( fp[i] ) ) {
			word = get_word ( line );
			if ( strcmp ( word , target ) == 0 ) {
				word = get_word ( line );
				if ( strcmp ( word, ":" ) == 0 )
					break;
			}
		}
		


		line = get_line ( f
	if ( target == NULL ) {
		for ( i = 0; fp[i]; i++ ) {
			while ( (line = get_line(fp[i])) != NULL) {
				target = get_word ( line );
				word = get_word ( line );
				if ( strcmp ( word, ":" ) == 0 )


				if ( strcmp ( word, ":" ) == 0 ) 
					continue;
				
				usr_tgt = malloc ( 2 * sizeof ( char * ) );
				usr_tgt[0] = strdup ( word );
				usr_tgt[1] = NULL;
			}
		}
		rewind ( fp[0] );
	}
	for ( j = 0 ; j < m; j++ ) 
		for ( i = 0; fp[i]; i++ ) {
			while ( tgt_flag == 0 && (line = get_line(fp[i])) != NULL ){
			printf ( "<%s>line\n",line );
				tab = 0;
				while ( tgt_flag == 0 && tab == 0 &&\
				(word = get_word (fp[i] ))!= NULL ) {
				printf ( "<%s -word>\n",word );
				printf ( "<%s -usr_tgt[%d]>\n", usr_tgt[j],j);
					if ( strcmp ( usr_tgt[j], word ) == 0 ) {
						tgt_flag = 1;
						first++;
					}
				}
			}
			if ( tgt_flag == 0 && first == 1) {
				fprintf ( stderr, "%s: target not found\n" );
				exit ( 4 );
			}
			for ( k = 0; k < tgt; k++ )
				if ( strcmp(word, all_tgt[k]) == 0 )
					break;
			if ( k == tgt ) {
				all_tgt = realloc ( all_tgt, (tgt + 2) * sizeof( char *) );
				all_tgt[tgt++] = strdup(word);
				all_tgt[tgt] = NULL;
			}
			word = get_word (fp[i] );
			if ( strcmp( word, ":" ) != 0  && first == 1) {
				fprintf ( stderr, "error in the make file\n" );
				first = 0;
				exit ( 1 );
			}
			else {
				word = get_word ( fp[i]);
				for ( k = 0; k < pt; k++ )
					if ( file_cont[pt] == ftell ( fp[i] ) )
						break;
				if ( k == pt ) {
					file_cont = realloc ( file_cont, 2 * sizeof ( int *));
					file_cont[pt++] = ftell ( fp[i] );
				}
				for ( k = 0; k < i-1; k++ ) 
					rewind ( fp[k] );
				for ( k =0; k <tgt; k++ )
					if ( strcmp ( word, all_tgt[k] )== 0 )
						break;
				if ( k == tgt ) {
					all_tgt = realloc ( all_tgt, (tgt + 2) * sizeof( char *) );
					all_tgt[tgt++] = strdup(word);
					all_tgt[tgt] = NULL;
				}
				pr_word = realloc ( pr_word, 2 * sizeof ( char * ) );
				pr_word[0] = strdup(word );
				pr_word[1] = NULL;
				printf ( "<%s-prword>\n",pr_word[0] );
				mymake ( fp, pr_word );
			}
			if ( word == NULL  || tgt_flag == 0) {
			// ACCESS the file existance	
				if ( tgt_flag == 0 ) {
					if ( access ( all_tgt[--tgt] , F_OK ) != 0 ) {
						fprintf ( stderr, "%s: No file exist\n", all_tgt[tgt] );
						exit ( 4 );
					}
					if ( stat ( all_tgt[tgt], &dpbuf ) == -1 ) {
						fprintf ( stderr, "dp stat failed\n" );
						exit ( 5 );
					}
					if ( stat ( all_tgt[--tgt], &tgbuf) == -1) {
						fprintf ( stderr, "tgt stat failed\n" );
						exit ( 6 );
					}
					if ( tgbuf.st_mtime < dpbuf.st_mtime )
						exec_commd = 1;
					else 
						printf ( "target is upto date\n");
				} 
				if ( tgt_flag == 1 || exec_commd == 1 ) {
					fseek ( fp[i], file_ptr[--ptr], SEEK_SET );
					while ( (line = get_line( fp[i] )) != NULL ) 
						while ( tab == 1 ) 
							while ( (word = get_word(fp[i] )) != NULL ) {
								commd = realloc ( commd,
											sizeof ( char *) * (cmd + 2 ));
								commd[cmd++] = strdup ( word );
									commd[cmd] = NULL;
							}
				}
				switch ( fork ( ) ) {
					case -1: 
						fprintf ( stderr, "fork failed\n" );
						exit ( 1 );
					case 0:
						execvp ( commd[0], commd );
						fprintf ( stderr, "exec failed\n" );
						exit ( 5 );
					default :
						break;
				}
				for ( i =0; i < cmd; i++ )
				free ( commd[i] );
				free(commd);
			}
	}
}

char * get_line ( FILE * fp ) {
	static int len = 0;
	static char * line;
	int offset;
#	define LEN	80 

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

char * get_word ( char * curr_line ) {
	static char * line;
	static char * word = NULL;
	static int len = 0;
	int k = 0;

	if ( curr_line != NULL )
		line = curr_line;
	if ( len <= strlen (line) )
		word = realloc ( word, strlen(line) + 1 );
	if ( *line == '\0' ) return NULL;
	while ( isblank ( *line ) ) line++;
	if ( *line == '#' || *line == '\n' ) return NULL;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}
