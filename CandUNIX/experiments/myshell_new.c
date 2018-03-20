# include <stdio.h>
# include <sys/types.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

void word_check ( char * );
void fork_exec ( char **, int *, char * );
char * get_token ( char * );
int isblank(int);

int pipe_active;
int pfd[2];

int main ( int argc, char *argv[] ) {
	FILE *fp;
	struct stat stbuf;
	char *string;
	int std_in = 0;

	string = malloc ( 100 );
	while ( *++argv ) {
		std_in = 1;
		if ( ! strcmp (*argv , "-" ) )
			while ( 1 ) {
				printf ( "[aruna@Uttara]$" );
				fgets ( string, 100, stdin );
				word_check ( string );
			}
		if ( stat (*argv, &stbuf ) == -1 ) {
			fprintf (stderr, "%s: it should be in text format\n" , *argv);
			exit ( 1 );
		}
		if ( geteuid() != 0 && ((getuid() == stbuf.st_uid) && !(stbuf.st_mode & 	         S_IRUSR)) && ((getegid() == stbuf.st_gid) && 
			 !(stbuf.st_mode & S_IRGRP )) && !(stbuf.st_mode & S_IROTH) ){
			fprintf ( stderr, "File is not having read perm\n" );
			exit ( 1 );
		}
		if ( ( fp = fopen ( *argv, "r" ) ) == NULL ) {
			fprintf (stderr, "file can't open \n " );
			exit ( 2 );
		}
		while ( fgets ( string, 100, fp ) != NULL ) 
			word_check ( string );
	}
	if ( !std_in ) 
	while ( 1 ) {
		printf ( "[aruna@Uttara]$" );
		pipe_active = 0;
		fgets ( string, 100, stdin );
		word_check ( string );
	}
	return 0;
}

void word_check ( char command[] ) {
	int flag[7];                                
	char **word, *file_name, *target, *std_in;  
	int i, j = 0, filename = 0, multi_amp = 0, multi_pipe = 0;
                                               
	pipe_active = 0;
	word = NULL; file_name = NULL;
	std_in = malloc ( 100 );
	for ( i = 0; i < 7; i++ ) flag[i] = 0; 
	printf ( "command is <%s>\n", command );
	if (strcasecmp ( command, "exit\n" ) == 0 ) exit ( 0 );
	printf ( "command is <%s>\n", command );
	while ( ( target = get_token ( command ) ) != NULL ) {
		command = NULL;
		printf ( "target is <%s>\n", target);
		if ( multi_amp || multi_pipe) {
			if ( !strcmp ( target, "\n" ) ) {
				fgets ( std_in, 100, stdin );
				flag[5] = 1;flag[3] = 0;
				fork_exec ( word, flag, file_name ); word = NULL;
				if ( multi_amp ) word_check ( std_in ); 
			} else if ( multi_pipe ) { 
				flag[5] = 1; flag[3] = 0;
				fork_exec ( word, flag, file_name );
				word = NULL;
				j = 0; 
				return; 
			} else { 
				flag[3] = 0;
				fork_exec( word, flag, file_name);
				word = NULL; j = 0; 
			}
			multi_amp = 0;
			multi_pipe = 0; 
		}
		if ( !strcmp ( target, ";" ) ) {
			fork_exec ( word, flag, file_name );
			word = NULL; j = 0; continue; 
		}
		if ( !strcmp ( target, "&" ) ) {
			flag[3] = 1;
			fork_exec ( word, flag, file_name );
			word = NULL; flag[3] = 0; j = 0;
			continue; 
		}
		if ( !strcmp ( target, "|" ) ) {
			flag[3] = 0; pipe_active += 2; flag[4] += 1;
			fork_exec ( word, flag, file_name ); 
			//pipe_active = 1;
			word = NULL; j = 0; continue; 
		}
		if ( !strcmp ( target, "&&" ) ) { 
			multi_amp = 1; flag[5] = 1; continue; 
		}
		if ( !strcmp ( target, "||" ) ) { 
			multi_pipe = 1; flag[5] = 1; continue; 
		}
		if ( !strcmp ( target, ">" ) ) { 
			if ( (flag[0] || flag[1]) && pipe_active ) {
				fork_exec ( word, flag, file_name ); word = NULL; j = 0; 
				pipe_active--;
			}
			flag[0] = 1; filename = 1; 
			continue;
		}
		if ( !strcmp ( target, "<" ) ) { 
			if ( flag[0] || flag[1] || pipe_active ) { 
				fork_exec ( word, flag, file_name ); word = NULL; j = 0; }
			flag[1] = 1; filename = 1; continue;
		}
		if ( !strcmp ( target, ">>" ) ) { 
			flag[6] = 1; filename = 1; continue; 
		}
		if ( filename ) {
			file_name = realloc ( file_name, sizeof ( target ) );
			file_name = strdup ( target );
			filename = 0; continue; 
		}
		word = realloc ( word, (++j) * sizeof ( target ) );
		word[j - 1] = strdup ( target );
		printf ( "word is <%s>\n", word[j - 1] );
		continue;
	}
	word[j - 1] = NULL;
	flag[5] = 1;
	if ( pipe_active >= 2 ) pipe_active = 1;
	fork_exec ( word, flag, file_name );
	return ;
}

void fork_exec ( char **word, int *flag , char *file_name) {
	FILE *fp;
	struct stat stbuf;
	char *str, *str1;
	int fd, i ;//, pfd[2]; 

	str = malloc (100);
	str1 = malloc (100);
	if ( !word[0] ) return;
	if ( !strcmp ( word[0], "cd" ) ) {
		chdir ( word[1] );
		system ( "pwd" );
		return;
	}
	if ( access ( word[0], F_OK ) == 0 ) {
		if ( stat (word[0], &stbuf ) == -1 ) {
			fprintf (stderr, "%s: it should be in text format\n", word[0]);
			exit ( 1 );
		}
		if ( geteuid() != 0 && ( (getuid() == stbuf.st_uid) && !(stbuf.st_mode & 	         S_IRUSR) ) && ( (getegid() == stbuf.st_gid) && 
			 !(stbuf.st_mode & S_IRGRP ) ) && !(stbuf.st_mode & S_IROTH) ){
			fprintf ( stderr, "/.%s permission denied \n", word[0]);
			exit ( 2 );
		}
		if ( geteuid() != 0 && ((getuid() == stbuf.st_uid) && !(stbuf.st_mode & 	         S_IXUSR)) && ((getegid() == stbuf.st_gid) && 
			 !(stbuf.st_mode & S_IXGRP )) && !(stbuf.st_mode & S_IXOTH) ){
			fprintf ( stderr, "/.%s permission denied \n", word[0]);
			exit ( 3 );
		}
		fp = fopen ( word[0], "r" );
		fgets ( str, 100, fp );
		rewind ( fp );
		if ( strstr ( str, "ELF" ) != NULL ) 
			;
		else  {
			while ( fgets ( str1, 100, fp ) != NULL ) 
				word_check ( str1 ); 
			return; }
	}
	if ( ( pipe_active  == 2 ) && ( pipe_active != 0 ) )
		if ( pipe ( pfd ) != 0 ) {
			fprintf ( stderr, "pipe is not created \n" );
			exit ( 1 );
		}
	if ( pipe_active > 0 ) 
		for ( i = 0; i < 7; i++ )
			flag[i] = 0;
	if ( fork () == 0 ) {
		if ( flag[0] ) {
			close ( 1 );
			printf ( "<<<<<<<<<<<<<<file_name = <%s>\n", file_name );
			fd = open ( file_name, O_CREAT | O_TRUNC | O_RDWR, 0666 );
		}
		if ( flag[6] )  {
			close ( 1 );
			fd = open ( file_name,  O_APPEND | O_RDWR, 0666 );
		}
		if ( flag[1] ) {
			close ( 0 );
			fd = open ( file_name, O_RDONLY, 0666 );
		}
		if ( flag[0] || flag[1] || flag[6] ) {
			if ( dup (fd) == -1 ) {
				fprintf ( stderr, "its not duplicating\n " );
				exit ( 3 );
			}
			flag[6] = 0; flag[0] = 0; flag[1] = 0;
		}
		if ( ( pipe_active  == 2 ) ) {
			printf ( "%dhai iam in pipe loop1******** \n" , pipe_active);
			close ( 1 );  
			//close ( pfd[0]);
			if ( dup ( pfd[1] ) != 1 ) {
				fprintf ( stderr, "its not duplicating\n" );
				exit ( 5 );
			}
		//	close ( 0 );
			close ( pfd[0] );
			close ( pfd[1] );
		} 

		if ( pipe_active > 2 ) {
		printf ( "???????In Pipe GT 2??????????\n" );
			close ( 0 ); 
			if ( dup ( pfd[0] ) != 0 ) {
				fprintf ( stderr, "its not duplicating2\n" );
				exit ( 5 );
			}
			printf ( " after dup 0 \n" );
			if ( !close ( 1 ) )
			   	 printf ( " close ( 1  ) succ \n" );
			else printf ( " close ( 1 ) fail \n" );
			
			printf ( " after close 1 \n" );
			if ( dup ( pfd[1] ) != 1 ) {
				fprintf ( stderr, "its not duplicating2\n" );
				exit ( 5 );
			}
		printf ( "???????END Pipe GT 2??????????\n" );
		} 
		if ( /*pipe_active % 2 == 1*/ pipe_active == 1 ) {
			printf ( "hai iam in pipe loop2 \n" );
			close ( 0 ); 
			close ( pfd[1]);
			if ( dup ( pfd[0] ) != 0 ) {
				fprintf ( stderr, "its not duplicating2\n" );
				exit ( 5 );
			}
		} 
		execvp ( word[0], word );
		fprintf ( stderr, "Invalid Command\n" );
		return;
	}
	if ( pipe_active == 1  ) { 
		close ( pfd[0] ); close ( pfd[1] ); 
		wait ( 0 );
	}
	if ( !flag[3] )  {  wait ( 0 ); } 
	return;
}

char word_collect[20] ;
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
		if ( *p == '<' ) { p++; return "<" ;}
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

 /* flag[0] --> navi_output
 	flag[1] --> navi_input
	flag[2] --> pipe
 	flag[3] --> & flag
	flag[4] --> pipe_counter
 	flag[5] --> ending of the program 
	flag[6] --> >> symbol */
