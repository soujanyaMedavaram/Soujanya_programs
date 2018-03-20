# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

char * get_word ( FILE *fp );		// Will overwrite previous word
									// if fp == NULL, will skip till eol.

int exec_commands ( char **commd, int ntokens ); 
int mymake ( FILE **fp, int nfp, char * target ); 

main ( int argc, char ** argv ) {
	FILE **fp = NULL; int nfp = 0;
	char **usr_tgts = NULL; int nusr_tgts = 0;
	char *token;
	int fflag = 0, i, ret;

	while ( *++argv ) {
		if ( strcmp ( *argv, "-f" ) == 0 ) {
			fflag = 1;
			continue;
		}
		if ( fflag ) {
			fp = realloc ( fp, (nfp + 1 ) * sizeof ( FILE * ) );
			fp[nfp++] = fopen ( *argv, "r" );
		}
		else {
			usr_tgts = realloc ( usr_tgts, (nusr_tgts + 1) * sizeof ( char *) );
			usr_tgts[nusr_tgts++] = strdup ( *argv );
		}
	}
	if ( nfp == 0 ) {
		fp = realloc ( fp, ( nfp + 1 ) * sizeof ( FILE * ) );
		fp[nfp++] = fopen ( "makefile", "r" );
		if ( fp[nfp-1] == NULL ) {
			fprintf ( stderr, "*** NO makefile to open\n" );
			exit ( 2 );
		}
	}
	if ( nusr_tgts == 0 ) {
		usr_tgts = realloc ( usr_tgts, (nusr_tgts + 1 ) * sizeof ( char * ) );
		token = get_word ( fp[0] );
		usr_tgts[nusr_tgts++] = strdup ( token ) ;
		token = get_word ( fp[0] );
		if ( strcmp (token, ":" ) != 0 ) {
			fprintf ( stderr, " *** missing seperator. Stop\n" );
			exit ( 3 );
		}
	}
	for ( i = 0; i < nusr_tgts; i++ ) {
		ret = mymake ( fp, nfp, usr_tgts[i] );
		if ( ret == 0 )
			continue;
		else if ( ret > 0 ) {
			fprintf ( stderr, "mymake: [%s] ", usr_tgts[i] );
			if ( ret > 2000 ) {
				fprintf ( stderr, " Error %d  (ignored)\n", ret - 2000 );
				continue;
			} else if ( ret > 1000 )
				 fprintf ( stderr, " Signal %d.  stop.\n", ret - 1000 );
			else fprintf ( stderr, " Error %d.\n", ret );
			exit ( 1 );
		}
		else if ( ret == -1 ) 
			fprintf ( stderr, "mymake: '%s' is up to date\n", usr_tgts[i]);
		else if ( ret == -2 ) 
			fprintf ( stderr, "mymake: Nothing to do for '%s'\n", usr_tgts[i] );
		else if ( ret == -3 ) 
			fprintf ( stderr, "mymake: No Rule to make target '%s'. Stop\n", 
				usr_tgts[i] );
		free ( usr_tgts[i] );
	}
	free ( usr_tgts );
	for ( i = 0; i < nfp; i++ )
		fclose ( fp[i] );
	free ( fp );
}

int mymake ( FILE **fp, int nfp, char * target ) {
	int at_flag, minus_flag, tgt_found, i, k, no_depend;
	char * tkn, * depend, * save_cmd;
	char **commd = NULL; int ntokens;
	int file_ptr, exec_cmd, exit_status;
	struct stat target_buf, dp_buf;

	tgt_found = 0;
	for ( i = 0; i < nfp; i++ ) {
		rewind ( fp[i] );
		while ( tkn = get_word ( fp[i] ) ) {
			if ( strcmp ( tkn, "\t" ) == 0 ) {		// Skip cmds
				next_line:
					get_word ( NULL );
					continue;
			}
			if ( strcmp ( tkn , "\n" ) == 0 ) continue;	
			if ( strcmp ( tkn, target ) ) goto next_line;
			if ( strcmp ( get_word ( fp[i] ), ":"  ) ) goto next_line;
			tgt_found = 1;
			break;
		}
		if ( tgt_found ) break;
	}
	if ( tgt_found == 0 ) {
		if ( access ( target, F_OK ) != 0 )
			return -3;
		return -2;
	}
	stat ( target, &target_buf );
	exec_cmd = 0; no_depend = 1;
	while ( tkn = get_word ( fp[i] ) ) {
		if ( strcmp ( tkn, "\n" ) == 0 ) break;		// End of dependancies
		no_depend = 0;
		file_ptr = ftell ( fp[i] );
		depend = strdup (tkn);
		exit_status = mymake ( fp, nfp, depend );
		if ( exit_status > 2000 )
			fprintf ( stderr, "mymake: [%s] Error %d.  (ignored)\n",
				depend, exit_status - 2000 );
		fseek ( fp[i], file_ptr, SEEK_SET );
		if ( exit_status > 0 && exit_status < 2000 )
			return exit_status;
		if ( exec_cmd ) continue; 
		if ( stat ( depend, &dp_buf ) < 0 ||
				target_buf.st_mtime < dp_buf.st_mtime ) 
			exec_cmd = 1;
	}
	if ( !no_depend && !exec_cmd )
		return -1;
	while ( tkn = get_word ( fp[i] ) ) {
		if ( strcmp ( tkn, "\t" ) ) break;
		ntokens = 0;
		while ( strcmp ( tkn = get_word (fp[i]), "\n" ) ) {
			commd = realloc ( commd, (ntokens + 2) * \
				sizeof ( char *));
			commd[ntokens++] = strdup ( tkn );
		}
		commd[ntokens] = NULL;

		save_cmd = *commd;  at_flag = minus_flag = 0;
		while ( **commd == '@' || **commd == '-' ) {
			if ( **commd == '@' ) at_flag = 1;
			else minus_flag = 1;
			++*commd;
		}
		if ( !at_flag ) {
			for ( k = 0; k < ntokens; k++ )
				printf ( "%s ", commd[k] );
			printf ( "\n" );
		}
		exit_status = exec_commands ( commd, ntokens );
		*commd = save_cmd;
		for ( k = 0; k < ntokens; k++ )
			free( commd[k] );
		free ( commd );
		commd = NULL;
		if ( minus_flag && exit_status > 0 && exit_status < 1000 )
			return exit_status + 2000;
		if ( exit_status && exit_status < 2000 )
			return exit_status;
	}
	return 0;
}

# define ROQ	50

char * get_word ( FILE * fp ) {
	int c, j;
	static char * word = NULL;
	static int len = 0;
	static int line_begins;
	static long save_pos;
	static FILE * sfp = NULL;
	int escape;

	if ( fp == NULL ) {
		while ( ( c = getc (sfp) ) != '\n' && c != EOF ) ;
		return;
	}
	if ( fp != sfp || ftell (fp) != save_pos )
		line_begins = 1;
	sfp = fp;
	escape = 0;
	while ( ( c = getc ( fp ) ) != EOF ) {
		save_pos = ftell (fp);
		if ( escape ) {
			if ( c != '\n' ) break;
			escape = 0;
			continue;
		}
		if ( c == '\\' ) {
			escape = 1; continue;
		}
		if ( c == '\t' && line_begins ) {
			line_begins = 0;
			return "\t";
		}
		line_begins = 0;
		if ( c == ' ' || c == '\t' ) continue;
		if ( c == '#' ) {
			get_word (NULL);
			line_begins = 1;
			continue;
		}
		if ( c == '\n' ) {
			line_begins = 1;
			return "\n";
		}
		if ( c == ':' ) return ":";
		break;
	}
	if ( c == EOF ) return NULL;
	j = 0;
	goto process_character;
	while ( 1 ) {
		c = getc (fp);
		process_character:
			if ( escape ) escape = 0;
			else {
				if ( c == '\\' ) escape = 1;
				else if ( c == ' ' || c == '\t' || c == '\n' ||
						c == ':' || c == EOF ) {
					if ( c == ':' || c == '\n' )
						ungetc (c, fp);
					word[j] = '\0';
					return word;
				}
			}
			if ( j >= len )
				word = realloc ( word, (len += ROQ) + 1 );
			word[j++] = c;
	}
}

/****
print_argv ( char **v ) {
	while ( *v)
		printf ( "%s\n", *v++ );
} ****/

int exec_commands ( char **commd, int ntokens ) {
	int exit_code;
	int ret_status;
	int term_sig;
	int wexit;
	int ret = 0;

	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "fork failed\n" );
			return 50;
		case 0:
		# ifdef TEST
			printf ( "I am child\n" );
			ret = 10 / ret;	
		# endif
			execvp ( *commd, commd );
			fprintf ( stderr, "exec failed\n" );
			return 51;
	}
	wait ( & exit_code );
	ret_status = WIFEXITED ( exit_code );
	printf ( "ret_status = %d\n", ret_status );
	if ( ret_status ) {
		 wexit = WEXITSTATUS ( exit_code );
		 printf ( "wexit = %d\n", wexit );
		 return wexit ;
	}
	else {
		term_sig =  WTERMSIG (exit_code);
		printf ( "term_sig = %d\n", term_sig );
		return 1000 + term_sig;
	}
}
/*int exec_commands ( char **commd, int ntokens ) {
	int exit_code;

	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "fork failed\n" );
			return 50;
		case 0:
			execvp ( *commd, commd );
			fprintf ( stderr, "exec failed\n" );
			return 51;
	}
	wait ( & exit_code );
	if ( WIFEXITED (exit_code) )
		 return WEXITSTATUS (exit_code);
	else return 1000 + WTERMSIG (exit_code);
}*/
