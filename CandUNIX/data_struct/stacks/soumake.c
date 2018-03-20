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
	char ** depends;  int ndepends;
	char * line, * word;
	struct stat dpbuf, tgtbuf;
	char *** commd = NULL; int ncmds; int ntokens;
	int first_word, at_d_rate, tgt_found;
	int i, j, k;
	
	first_word = at_d_rate = tgt_found = 0;	
	depends = malloc ( sizeof (char *) );
	ndepends = 0;
	commd = malloc ( sizeof (char *) );
	ncmds = 0;
	commd[ncmds] = malloc ( sizeof (char *) );
	ntokens = 0;
	for ( i = 0; fp[i]; i++ )
		rewind ( fp[i] );
	if ( !target ) {
	printf ( "target is NULL\n" );
		line = get_line ( fp[0] );
		printf ( "<%s>\n", line );
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
	rewind ( fp[0] );
	for ( i = 0; fp[i]; i++ ) {
		while ( line = get_line ( fp[i] )){ 
		printf ( "<%s>==line\n" ,line);
			word = get_word ( line );
			if ( strcmp ( word , target ) != 0 ) 
				continue;
			word = get_word ( NULL );
			if ( strcmp ( word, ":" ) != 0 ) {
				fprintf ( stderr, "*** missing seperator. Stop \n" );
				exit ( 3 );
			}
			tgt_found = 1;
				while ( word = get_word ( NULL ) ) {
				depends[ndepends] = strdup ( word );
				depends = realloc ( depends, (++ndepends + 1 ) * \
				sizeof ( char * ) );
			}
			depends[ndepends] = NULL;
			for ( k = 0; k < ndepends; k++ )
				printf ( "<%s>depend\n", depends[k] );
			break;
		}
		while ( line = get_line ( fp[i] ) ) {
		printf ( "<%s>->line\n" , line );
			first_word = 0;
			ntokens = 0;
			if ( line[0] == '\t') {
				while ( word = get_word ( line ) ) {
					if ( first_word == 0 )
						line = NULL;
						if ( word[0] == '@' ){
							word ++;
							at_d_rate = 1;
						}
					commd[ncmds][ntokens] = strdup ( word );
					commd[ncmds] = realloc ( commd[ncmds], (++ntokens + 1 )\
						* sizeof (char * ) );
				}
				commd[ncmds][ntokens] =NULL;
				commd = realloc ( commd, (++ncmds + 1) * \
				sizeof ( char * ) );
				commd[ncmds] = malloc ( sizeof ( char * ) );
			}
			else break;
		}
		commd[ncmds] = NULL;
		for ( k = 0; commd[k]; k++ ) 
			for ( j =0; commd[k][j]; j++ )
				printf ( "<%s>cmd\n",commd[k][j] );
		for ( k = 0; k < ndepends; k++ ){
		printf ( "<%s>call\n", depends[k] );
			mymake ( fp, depends[k] );
		}
	}
	if ( tgt_found == 0 ) {
		if ( access ( target , F_OK ) != 0 ) {
			fprintf ( stderr, "No Rule to make target '%s'\n", target );
			exit ( 5 );
		}
		return;
	}
	printf ( "<%s>==>target\n", target );
	if ( stat ( target, &tgtbuf ) == -1 ) {
		fprintf ( stderr, " stat failed for target<%s>\n", target );
		exit ( 3 );
	}
	for ( k = 0; depends[k]; k++ ) {
		if ( stat ( depends[k], &dpbuf ) == -1 ) {
			fprintf ( stderr, "stat failed for depend<%s>\n", depends[k] );
			exit ( 4 );
		}
		if ( tgtbuf.st_mtime < dpbuf.st_mtime ) {
			for ( j = 0; commd[j]; j++ ) {
				switch ( fork ( ) ) {
					case -1:
						fprintf ( stderr, "fork failed\n" );
						exit ( 5 );
					case 0:
						execvp ( commd[j][0], commd[j] );
						fprintf ( stderr, "exec failed \n" );
						exit ( 6 );
					default :
						if ( at_d_rate == 0 ) 
						printf ( "%s\n",commd[j] );
						break;
				}	
			}
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
	if ( *line == '\0' ) return NULL;
	while ( isblank ( *line ) ) line++;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}
