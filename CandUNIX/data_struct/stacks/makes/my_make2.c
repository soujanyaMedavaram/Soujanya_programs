# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <stdlib.h>

int m, f1;
main ( int argc, char *argv[] ) {
	char ** usr_tgt;
	FILE **fp = NULL, *tempfp;
	int file_found, tgt_found;

	m = f1 = file_found = tgt_found = 0;
	while ( *++argv ) {
		if ( strcmp(*argv, "-f") == 0 ) {
			file_found = 1;
			argv++;
			tempfp = fopen ( *argv, "r" );
			if ( tempfp == NULL ) {
				fprintf ( stderr, "%s: file not opened\n", *argv );
				exit ( 2 );
			}
			fp = realloc (fp, (f1 + 2 ) * sizeof ( FILE *));
			fp[f1++] = tempfp;
			fp[f1] = NULL;
			continue;
		}
		usr_tgt = malloc ( (m + 2) * sizeof ( char *) );
		usr_tgt[m++] = strdup(*argv);
		usr_tgt[m] = NULL;
		tgt_found = 1;
	}
	if ( file_found == 0 ) {
		tempfp = fopen ( "makefile","r");
		if ( tempfp == NULL ) {
			fprintf ( stderr, "make file not opened\n" );
			exit ( 4 );
		}
		fp = realloc (fp, (f1+2) * sizeof ( FILE *));
		fp[f1 - 1] = tempfp;
		fp[f1] = NULL;
	}
		mymake(fp, usr_tgt );
	for ( i = 0; i < f1; i++ )
		fclose ( fp[i]);
	for (i = 0; i < m; i++)
		free( usr_tgt[i] );
	free( usr_tgt);
	free( fp );
}

char **all_tgt;
int tab = 1;

void mymake ( FILE **fp, char **usr_tgt) {
	int tgt_flag, tgt;

	char *pr_word = NULL;
	tgt_flag = tgt = 0;
	static first = 0;
	if ( usr_tgt == NULL ) {
		while ( tgt_flag == 0 ) {
			line = get_line ( fp[0] );
			while ( (word = get_word ( line )) != NULL && tgt_flag == 0) {
				if ( strcmp ( word, ":" ) == 0 ) {
					tgt_flag = 1;
					continue;
				}
				free ( pr_word );
				pr_word = malloc ( strlen ( word ) + 1 );
				strcpy ( pr_word, word );
			}
		}
		rewind ( fp[0] );
		mymake ( fp, pr_word); 
	}
	else { // usr_tgt is not NULL
		for ( i = 0 ; i < f1; i++ ) 
			if ( tgt_flag == 0 ) {
				while ( tgt_flag == 0 && (line = get_line(fp[i])) != NULL )
					while ( (word = get_word ( line )) && tgt_flag == 0 ) 
						if ( strcmp ( usr_tgt, word ) == 0 ) {
							tgt_flag = 1;
							first++;
						}
			}
		if ( tgt_flag == 0 && first == 0) {
			fprintf ( stderr, "%s: target not found\n" );
			exit ( 4 );
		}
		all_tgt = realloc ( all_tgt, (tgt + 2) * sizeof( char *) );
		all_tgt[tgt++] = strdup(word);
		all_tgt[tgt] = NULL;
		word = getword ( line );
		if ( strcmp( word, ":" ) != 0 ) {
			fprintf ( stderr, "error in the make file\n" );
			exit ( 1 );
		}
		word = get_word ( line );
		if ( word != NULL )
			mymake ( fp, word );
		if ( word == NULL  || tgt_flag == 0) {
		// ACCESS the file existance	
			if ( access ( all_tgt[--tgt] , F_OK ) != 0 ) {
				fprintf ( stderr, "%s: No file exist\n", all_tgt[tgt] );
				exit ( 4 );
			}
			while ( (line = get_line( fp[i] ) != NULL ) {
				while ( tab == 1 ) 
				while ( (word = get_word( line )) != NULL ) {
					commd = realloc ( commd, sizeof ( char *) * (cmd + 2 ));
					commd[cmd++] = strdup ( word );
					commd[cmd] = NULL;
				}
				switch ( fork ( ) ) {
					case -1: 
						fprintf ( stderr, fork failed\n" );
						exit ( 1 );
					case 0:
						execvp ( commd[0], commd );
						fprintf ( stderr, "exec failed\n" );
						exit ( 5 );
					default :
						break;
				}
		}
		else {
			for ( j = 0; j < i; j++ )
				rewind ( fp[i] );
			mymake ( fp, word );
		}

		

}

	
# define LEN 2 
char * get_line ( FILE *fp ) {
printf ( "\n in getline\n" );
	static char *line;
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
				line[strlen(line)] = '\n';
				line[strlen(line)+1] = '\0';
				return line;
			line[strlen(line) - 1 ] = ' ' ;
		}
		offset = strlen(line);
	}
}
