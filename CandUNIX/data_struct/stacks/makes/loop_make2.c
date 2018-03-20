
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

void mymake ( FILE **fp, char *target ) {
	int i, j, no_depends, first_line, tgt_found;
	char **all_targets, ntargets;
	char **all_depends, ndepends;
	char ***all_cmds, ncmds, ntokens;	
	char *line, *word;
	struct stat tgt_buf, dp_buf;
	int label;

	all_targets = malloc ( sizeof (char *) ); ntargets = 0;
	all_depends = malloc ( sizeof (char *) ); ndepends = 0;
	all_cmds = malloc ( sizeof (char *) ); ncmds = 0;
	all_cmds[ncmds] = malloc ( sizeof (char *) ); ntokens = 0;
	label = 0;
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
	}
	rewind ( fp [0] );

	collect :

	for ( i = 0; fp[i]; i++ ) {
		first_line = 0;
		tgt_found = 0;
		while ( line = get_line ( fp[i] )) {
			if ( line[0] != '\t' ) {
				first_line++;
				word = get_word ( line );
				if ( strcmp ( word, target ) != 0 ) 
					continue;
				word = get_word ( NULL );
				if ( strcmp ( word, ":") != 0 ) {
					fprintf ( stderr, "*** NO rule to make target '%s'\n", target );
					exit ( 3 );
				}
				tgt_found = 1;
				all_targets[ntargets] = strdup ( target );
				all_targets = realloc ( all_targets, ( ++ntargets + 1 )\
					* sizeof (char * ));
				while ( word = get_word ( NULL ) ) {
					no_depends = 0;
					all_depends[ndepends] = strdup ( word );
					all_depends = realloc ( all_depends, (++ndepends + 1 ) * \
						sizeof ( char * ) );
				}
				all_depends[ndepends] = strdup ( "$depend$" );
				all_depends = realloc ( all_depends, (++ndepends + 1 ) * \
					sizeof ( char * ) );
				all_depends[ndepends] = NULL;
				line = get_line ( fp[i] );
				if ( line[0] == '\t' ) {
					if ( first_line == 0 ) {
						fprintf ( stderr, "command commence before target\n" );
						exit ( 4 );
					}
					else {
						while ( word = get_word( line ) ) {
							line = NULL;
							all_cmds[ncmds][ntokens] = strdup ( word );
							printf ( "<%s>->all_cmds[nc][nt]\n", \
							all_cmds[ncmds][ntokens] );
							all_cmds[ncmds] = realloc ( all_cmds[ncmds], \
								sizeof ( char * ) * (++ntokens + 1 ) );
						}
						all_cmds[ncmds][ntokens] = NULL;
						ntokens = 0;
						all_cmds = realloc ( all_cmds, sizeof ( char *) *\
							(++ncmds + 1 ) );
						all_cmds[ncmds] = realloc ( all_cmds[ncmds], \
						sizeof ( char * ) );
						all_cmds[ncmds][ntokens] = strdup ( "$commd$" );
						all_cmds[ncmds] = realloc ( all_cmds[ncmds],\
							sizeof ( char * ) * (++ntokens + 1 ) );
						all_cmds[ncmds][ntokens] = NULL;
						ntokens = 0;
						all_cmds = realloc ( all_cmds, sizeof ( char * ) *\
							(++ncmds + 1 ) );
						all_cmds[ncmds] = malloc ( sizeof(char *) );
					}
						//all_cmds[ncmds] = NULL; do it in last
					}
				}
				if ( tgt_found == 0 )
					continue;
				while (  label < ndepends  ) {
					strcpy ( target, all_depends[label] );
					label++;
					for ( j =0; j <= i; j++ )
						rewind ( fp[i] );
						goto collect;
					}
		}			
	}
	all_targets[ntargets] = NULL;
	//all_depends[ndepends] = NULL;
	all_cmds[ncmds] = NULL;
	printf ( "\n targets \n" );
	for ( i =0; i < ntargets; i++ )
		printf ( "<%s>\n", all_targets[i] );
	printf ( "\n depends \n" );
	for ( i =0; i < ndepends; i++ )
		printf ( "<%s>\n", all_depends[i] );
	printf ( "\n commands\n" );
	for ( i =0; i < ncmds; i++ ){
		for ( j = 0; all_cmds[j]; j++ )
			printf ( " <%s>", all_cmds[i][j] );
		printf ( "\n" );
	}
	*all_depends++;
	all_cmds++;
	for ( i = 0; all_targets[i]; i++ ) {
		stat ( all_targets[i] , &tgt_buf);
		while ( *all_depends && (strcmp ( *all_depends, "$depend$" ) )) {
			if ( access ( *all_depends, F_OK ) != 0 ) {
				fprintf ( stderr, "*** '%s' file does not exist\n",\
					*all_depends );
				exit ( 5 );
			}
			if ( stat ( *all_depends, &dp_buf ) == -1 ) {
				fprintf ( stderr, "stat failed for depend '%s'\n", \
					*all_depends );
				exit ( 6 );
			}
			if ( tgt_buf.st_mtime < dp_buf.st_mtime ) {
			all_cmds++;
			printf ( "<%s>->cmds\n", **all_cmds );
				while ( strcmp ( **all_cmds, "$commd$" ) != 0 ) {
				printf ( "\n in while\n" );
					switch ( fork ( ) ) {
						case -1:
							fprintf ( stderr, "fork failed\n" );
							exit ( 6 );
						case 0:
							execvp ( **all_cmds, *all_cmds );
							fprintf ( stderr, "failed at exec\n" );
							exit ( 7 );
						defult :
						while ( **all_cmds ){
							printf ( "%s  ",**all_cmds );
							*all_cmds++;
						}
						printf ( "\n" );
						wait ( 0 );
					}
					all_cmds++;
				}
			}
			all_depends++;
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
	if ( len <= strlen (line) ){
		len = strlen ( line );
		word = realloc ( word, strlen(line) + 1 );
	}
	while ( isblank ( *line ) ) line++;
	if ( *line == '\0' || *line == '\n') return NULL;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}
