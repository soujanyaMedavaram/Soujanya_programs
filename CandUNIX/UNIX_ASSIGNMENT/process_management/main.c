# include <stdio.h>
# include <sys/types.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

# define MAX	100
# define TRUE	1
# define FALSE	-1	

struct flags {
	int pipe_active;
	int ncmd;
	int or_flag;
	int dgt;
	int gt;
	int lt;
	int amp;
} flag;

char word_collect[20] ;
char **dir_list;
int ndir, pfd1[2], pfd2[2];

void interpret ( char **, int, int );
void cmd_prompt ( );
void cmd_check ( char ** );
char * get_token ( char * );
int fork_exec ( char **, char * );
int isblank ( );

int main ( int argc, char *argv[] ) {
	char **collect_words = NULL;
	char *path, directory[50];
	int std_in = 0, ncollect = 0, j = 0,i = 0;

	dir_list = NULL; ndir = 0;
	pipe ( pfd1 );
	pipe ( pfd2 );
	path = getenv ( "PATH" );
	for ( ; *path != '\0' ; path++ ) {
		if ( *path == ':' ) {
			directory[i] = '\0';
			dir_list = realloc ( dir_list , ( ndir + 2 ) * sizeof ( char *) );
			dir_list[ndir++] = strdup ( directory );
			i = 0;
			continue;
		}
		directory[i++] = *path;
	}
	directory[i] = '\0';
	dir_list[ndir++] = strdup ( directory );
	dir_list[ndir] = NULL;
	printf ( "Finished reading env\n" );
	printf ( " before while \n" );
	while ( *++argv ) {
	printf ( " hello: in while\n" );
		std_in = 1;
		if ( strcmp ( *argv , "-" ) )
		{
			collect_words = realloc( collect_words, 
										( ncollect + 2 ) * sizeof ( char * ) );	
			collect_words[ncollect++] = strdup ( *argv );
		}
		else {
			if ( collect_words ) {
				collect_words[ncollect] = NULL;
				interpret ( collect_words , ncollect, FALSE);
				for ( j = 0; collect_words[j]; j++ )
					free ( collect_words[j] );
				free ( collect_words );
				collect_words = NULL;
				ncollect = 0;
				cmd_prompt ( );
			}
		}
	}
	printf ( "out of while\n" );
	if ( collect_words ) {
		collect_words[ncollect] = NULL;
		interpret ( collect_words, ncollect, FALSE );
	}
	if ( !std_in ) 
		cmd_prompt ( );
	return 0;
}

void cmd_prompt ( ) {
	char **collect_words = NULL, *token, *line;
	int j, ncollect = 0;

	while ( 1 ) {
		printf ( "[myshell@Uttara]$" );
		token = malloc ( 20 );
		line = malloc ( MAX );
		ncollect = 0;
		fgets ( line, MAX, stdin );
		while ( (token = get_token ( line ) ) != NULL ) {
			line = NULL;
			collect_words = realloc ( collect_words, ( ncollect + 2 ) 
									* sizeof ( char * ) );
			collect_words[ncollect++] = strdup ( token );
		}
		collect_words[ncollect] = NULL;
		if ( strcasecmp ( collect_words[0], "exit" ) == 0 ) exit ( 0 );
		interpret ( collect_words, ncollect, FALSE );
		for ( j = 0; collect_words[j]; j++ ) free ( collect_words[j] );
		free ( collect_words ); collect_words = NULL;
		free ( line ); free ( token );
	}
	return;
}

void cmd_check ( char **cmd_words ) {
	char **word = NULL, *file_name = NULL;
	int filename ;
	int i  = 0 , exit_code ;
	int nwords , j;

	CMD_CHK:
	flag.amp = flag.gt = flag.lt = flag.dgt = filename = nwords = 0;
	exit_code = 2;
	printf ( " In cmd_check\n" );
	for (  j = 0; cmd_words[j]; j++ ) 
		printf ( "<%s>->cmd_words\n", cmd_words[j] );
	printf ( "<%s>->cmd_words[NULL]\n", cmd_words[j] );
	printf ( "%d->static i \n", i );
	for ( ; cmd_words[i]; i++ ) {
		if ( flag.or_flag ) {
			flag.or_flag = 0;
			if ( !exit_code ) 
				return;
		}
		if ( !strcmp ( cmd_words[i], "\n" ) ) { flag.pipe_active = 1; continue; }
		if ( !strcmp ( cmd_words[i], ";"  ) ) break;
		if ( !strcmp ( cmd_words[i], "&&" ) ) break;
		if ( !strcmp ( cmd_words[i], "||" ) ) { 
			flag.or_flag = 1;
			break; 
		}
		if ( !strcmp ( cmd_words[i], "|"  ) ) { 
			flag.pipe_active += 2; 
			flag.ncmd += 1;
			break;
		}
		if ( !strcmp ( cmd_words[i], "&"  ) ) { flag.amp = 1; break; }
		if ( !strcmp ( cmd_words[i], ">"  ) ) { flag.gt = 1; filename = 1;  }
		if ( !strcmp ( cmd_words[i], ">>" ) ) { flag.dgt = 1; filename = 1; }
		if ( !strcmp ( cmd_words[i], "<"  ) ) { flag.lt = 1; filename = 1;  }
		if ( filename ) {
			file_name = strdup ( cmd_words[i] );
			filename = 0;
			continue;
		}
		word = realloc ( word, ( nwords + 2 ) * sizeof ( char * ) );
		word[nwords++] = strdup ( cmd_words[i] );
	}
	word[nwords] = NULL;
	exit_code = fork_exec ( word, file_name );
	for ( j = 0; j < nwords; j++ )
		free ( word[j] );
	free ( word );
	free ( file_name );
	file_name = NULL;
	word = NULL;
	nwords = 0;
	printf ( "\n exit_code = %d\n", exit_code );
	if ( cmd_words[i] != NULL )
		goto CMD_CHK;
		//cmd_check ( cmd_words );
			
	return;
}

int fork_exec ( char **word, char *file_name) {
	int fd, exit_code; 

	for ( exit_code = 0; word[exit_code]; exit_code++ )
		printf ( "<%s>->for_exec\n", word[exit_code] );
	switch ( fork  (  ) ) {
		case -1 :
			fprintf ( stderr, " fork failed\n" );
			exit ( 1  );
		case 0:
		if ( ( flag.pipe_active  == 2 ) ) {
			close ( 1 );
			if ( dup ( pfd1[1] ) != 1 ) {
				fprintf ( stderr, " dup1 failed \n" );
				exit ( 1  );
			}
			close ( pfd1[1] );
		} 

		if ( flag.pipe_active > 2 ) {
			if ( ( flag.ncmd % 2 ) == 0 ) {
				close ( 0 );
				if ( dup ( pfd1[0] ) != 0 ) {
					fprintf ( stderr, " dup4 failed\n" );
					exit ( 4 );
				}
				close ( pfd1[0] );
				close ( 1 );
				if ( dup ( pfd2[1] ) != 1 ) {
					fprintf ( stderr, " dup5 failed\n" );
					exit ( 4 );
				}
				close ( pfd2[1] );
			}
			if ( ( flag.ncmd % 2 ) != 0 ) {
				close ( 0 );
				if ( dup ( pfd2[0] ) != 0 ) {
					fprintf ( stderr, "dup6 failed\n" );
					exit ( 5 );
				}
				close ( pfd2[0] );
				close ( 1 );
				if ( dup ( pfd1[1] ) != 1 ){
					fprintf ( stderr, " dup7 failed\n" );
					exit ( 5 );
				}
				close ( pfd1[1] );
			}
		} 
		if ( flag.pipe_active == 1 ) {
			close ( 0 );
			if ( ( flag.ncmd % 2 ) == 0 ) {
				if ( dup ( pfd1[0] ) != 0 ) {
					fprintf ( stderr, "dup2 failed \n" );
					exit ( 2 );
				}
				close ( pfd1[0] );
			}
			else if ( (flag.ncmd % 2 ) != 0 ) {
				if ( dup ( pfd2[0] ) != 0 ) {
					fprintf ( stderr, " dup3 failed \n" );
					exit ( 1  );
				}
				close ( pfd2[0] );
			}
		} 
		if ( flag.gt ) {
			close ( 1 );
			fd = open ( file_name, O_CREAT | O_TRUNC | O_RDWR, 0666 );
		}
		if ( flag.dgt )  {
			close ( 1 );
			fd = open ( file_name,  O_APPEND | O_RDWR, 0666 );
		}
		if ( flag.lt ) {
			close ( 0 );
			fd = open ( file_name, O_RDONLY, 0666 );
		}
		if ( flag.gt || flag.lt || flag.dgt ) {
			if ( dup (fd) == -1 ) {
				fprintf ( stderr, "its not duplicating\n " );
				exit ( 3 );
			}
		}
		execvp ( word[0], word );
		fprintf ( stderr, "Invalid Command\n" );
		exit ( 1 );	

		default :	
			if( !flag.amp /*&& pipe_active != 1*/)  {  
					wait ( &exit_code );  
				if ( WIFEXITED ( exit_code ) )
					return WEXITSTATUS ( exit_code );
				else return 10;
			}
	}
}


char * get_token ( char * line ) {
	static char *p;		
	int j;

//	word = malloc ( 20 );
	if ( line != NULL )
		p = line;
	for ( ; isblank( *p ); p++ )
	;
	for ( j = 0; *p != '\0';  p++ ) {
		if ( *p == ';' || *p == '|' || *p == '&' || isblank (*p) 
			|| *p == '\n' || *p == '>' || *p == '<' ) {
			word_collect[j] = '\0'; 
			if ( word_collect[0] != '\0' ) return word_collect;
		}
		if ( *p == '\n' ) { p++; return "\n" ; }
		if ( *p == '<' ) { p++; return "<" ; }
		if ( *p == ';' ) { p++; return ";" ; }
		if ( *p == '|' && *(p + 1) == '|' ) { p += 2 ; return "||"; }
		else if ( *p == '|' ) { p++; return "|" ; }
		if ( *p == '&' && *(p + 1) == '&' ) { p += 2 ; return "&&"; }
		else if ( *p == '&' ) {p++; return "&" ; }
		if ( *p == '>' && *(p + 1) == '>' ) { p += 2 ; return ">>"; }
		else if ( *p == '>' ) {p++; return ">" ; }
		word_collect[j++] = *p;
	}
	if ( *p == '\0' ) return NULL;
	return NULL;
}

void interpret ( char **cmd_arg, int narg, int cmd_pmpt ) {
	FILE *fp;
	int path_name, i;
	char **line_words = NULL, *temp_dir ; int nwords;
	char *line, *token;
	struct stat stbuf;
	
	token = malloc ( MAX );
	line = malloc ( MAX );
	if ( strstr ( cmd_arg[0], "./" ) != NULL )
		path_name = TRUE;
	else if ( strstr ( cmd_arg[0], "../" ) != NULL )
		path_name = TRUE;
	else path_name = FALSE;
	if ( path_name == TRUE ) ;
	else if ( path_name == FALSE ) {
		for ( i = 0; i < ndir; i++ ) {
			temp_dir = malloc (strlen ( dir_list[i] ) + 
									strlen ( cmd_arg[0] ) + 1 );
			strcpy ( temp_dir, dir_list[i] );
			strcat ( temp_dir, "/" );
			strcat ( temp_dir, cmd_arg[0] );
			if ( !access ( temp_dir, F_OK ) ) {
				free ( cmd_arg[0] );
				cmd_arg[0] = strdup ( temp_dir );
				break;
			}
			else { free ( temp_dir ); temp_dir = NULL; }
		}
	}
	if ( i == ndir ) {
		fprintf ( stderr, "No such file or directory \n" );
		exit ( 3 );
	}
	if ( geteuid() != 0 && ((getuid() == stbuf.st_uid) && !(stbuf.st_mode & 	         S_IRUSR)) && ((getegid() == stbuf.st_gid) && 
		 !(stbuf.st_mode & S_IRGRP )) && !(stbuf.st_mode & S_IROTH) ){
		fprintf ( stderr, "/.%s: permission denied\n", cmd_arg[0] );
		exit ( 1 );
	}
	if ( cmd_pmpt == TRUE ) 
		if ( geteuid() != 0 && ((getuid() == stbuf.st_uid) && !(stbuf.st_mode & 	         S_IXUSR)) && ((getegid() == stbuf.st_gid) && 
			 !(stbuf.st_mode & S_IXGRP )) && !(stbuf.st_mode & S_IXOTH) ){
			fprintf ( stderr, "/.%s: permission denied\n", cmd_arg[0] );
			exit ( 1 );
		}
	fp = fopen ( cmd_arg[0], "r" );
	if ( fp == NULL ) {
		fprintf ( stderr, "Unable to open file\n" );
		exit ( 1 );
	}
	fgets ( line, MAX, fp );
	if ( strstr ( line, "ELF" ) != NULL ) 
		cmd_check ( cmd_arg );
	else {
		rewind ( fp );
		while ( fgets ( line, MAX, fp ) ) {
			while ( ( token = get_token ( line ) ) ) {
				line = NULL;
				line_words = realloc ( line_words, ( nwords + 2 ) *
										sizeof ( char * ) );
				if ( !strcmp ( token, "$1" ) ) i = 1;
				else if ( !strcmp ( token , "$2" ) ) i = 2;
				else if ( !strcmp ( token, "$3" ) ) i = 3;
				else if ( !strcmp ( token, "$4") ) i = 4;
				if ( narg >=( i+1 ) ) strcpy ( token, cmd_arg[i] );
				else strcpy ( token,"\n" );
				line_words[nwords++] = strdup ( token );
			}
			line_words[nwords] = NULL;
			interpret ( line_words, nwords, TRUE );
			for ( i = 0; i <= nwords; i++ ) {
				free ( line_words[i] );
				free ( line_words );
			}
			line_words = NULL;
		}
	}
	printf ( " \n cmd_chk returned \n" );
	free ( token );
	printf ( " free( token )\n" );
}
