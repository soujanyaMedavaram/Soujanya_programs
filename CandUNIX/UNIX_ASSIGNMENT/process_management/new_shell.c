# include <stdio.h>
# include <errno.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

void file_exec( FILE *fp );
void gtfunc ( );
void ltfunc ( );
void ppfunc ( );
void func ( );
void digifunc ( int num );

char **word1 = NULL , **word2 = NULL, commd[25];
int   nwords = 0;

main (int argc, char *argv[] ) {
	struct stat stbuf;
	FILE *fp;
	if ( argc > 1 ) {
		while ( *++argv ) {
			if ( stat ( *argv, &stbuf ) == -1 ) {
				fprintf ( stderr, "stat failed \n" );
				exit ( -1 );
			}
			if ( stbuf.st_mode & S_IXUSR ) {
				if ( (fp = fopen ( *argv, "r" )) == NULL ) {
					fprintf ( stderr, "fopen failed \n" );
					exit ( 1 );
				}
			} else {
				fprintf ( stderr, "file is not having exe permission\n" );
				exit ( 20 );
			}
			file_exec ( fp );
			fclose ( fp );
		}
	}
	if ( argc == 1 )
		file_exec ( stdin );
	exit ( 0 );
}

void file_exec ( FILE *fp ) {
	int  gtflag, ltflag, ppflag, r1,r2, j, i, m, num;
	int  flag = 0;
	char word[10] ;
	
	switch ( fork ( ) ) {
		case -1:
				fprintf ( stderr, "fork failed \n" );
				exit ( 1 );
		case 0:
				while ( 1 ) {
					m = 1;
					num = 0;
					word1 = NULL;
					word2 = NULL;
					flag = 1;
					gtflag = ltflag = ppflag = r1 = r2 = j = 0;
					if ( fp == stdin )
						printf ( "sou>" );
					if ( fgets ( commd, 25, fp ) == NULL )
						exit ( 0 );
					if ( !strcmp ( commd, "exit\n" ) )
						exit ( 0 );
					i = 0;
					while ( commd[i] != '>' && commd[i] != '<' 
						&& commd[i] != '|' && commd[i] != '\0' ) {
						if ( commd[i] == ' '  || commd[i] == '\n') {
							word[j] = '\0';
							if ( j > 0 ) {
								word1 = realloc (word1, sizeof (char *) * ++m );
								word1[r1++] =  strdup(word) ;
							}
							j= 0;
							i++;
							if ( commd[i] == '1' || commd[i] == '2' ) {
								num = atoi ( &commd[i++] );
								if ( commd[i] != '>' ) {
									fprintf ( stderr,"wrong format command\n" );
									exit ( -1 );
								}
							}
							else if ( commd[i] == '>' )
							;	
							continue;
						}
						word[j++] = commd[i];
						i++;
					}
					word1[r1] = NULL;
				if ( commd[i] != '\0' ) {
						if ( commd[i] == '>' )
							gtflag = 1;
						else if (commd[i] == '<' )
							ltflag = 1;
						else if (commd[i] == '|' )
							ppflag = 1;
						i++, j = 0;
						while ( commd[i] != '\0' ) {
							if ( commd[i] == ' ' || commd[i] == '\n') {
								word[j] = '\0';
								if ( j > 0 ) {
									word2 = realloc ( word2, sizeof (char *)  );
									word2[r2++] = strdup(word);
								}
								j = 0;
								i++;
								continue;
							}
							word[j++] = commd[i];
							i++;
						}
						word2[r2] = NULL;	
					}
					if ( gtflag == 1 && num == 0)
						gtfunc ( );
					else if (ltflag == 1 )
						ltfunc ( );
					else if ( ppflag == 1 )
						ppfunc ( ); 
					else if ( num != 0 )
						digifunc ( num );
					else 
						func ( );
			}
	}
	wait ( 0 );
}

void gtfunc( ) {
	int fd;
	switch ( fork ( ) ) {
		case -1 :
				fprintf ( stderr, "fork failed \n" );
				exit ( 1 );
		case 0:
				fd = open ( word2[0], O_CREAT | O_TRUNC | O_WRONLY, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "gt - open failed \n" );
					exit ( 2 );
				}
				close ( 1 );
				if ( dup ( fd ) != 1 ) {
					fprintf ( stderr, "gt - dup failed\n" );
					exit ( 3 );
				}
				close ( fd );
				execvp ( word1[0], word1 );
				fprintf ( stderr, "gt - no such command %s\n", *word1);
				exit ( 4 );
	}
	wait(0);
	return;
}

void ltfunc ( ) {
	int fd;
	
	switch ( fork ( ) ) {
		case -1:
				fprintf ( stderr, "fork failed \n" );
				exit ( 5 );
		case 0:
				fd = open ( word2[0], O_RDONLY, 0600 );
				if ( fd < 0 ) {
					fprintf ( stderr, "lt - open failed \n" );
					exit ( 6 );
				}
				close ( 0 );
				if ( dup ( fd ) != 0 ) {
					fprintf ( stderr, "lt - dup failed \n" );
					exit ( 7 );
				}
				close ( fd );
				execvp ( word1[0], word1 );
				fprintf ( stderr, "lt - no such command %s > %s\n" , *word1, word2[0]);
				exit ( 8 );
	}
	wait(0);
	return;
}

void ppfunc ( ) {
	int pfd[2];
	if ( pipe ( pfd ) < 0 ) {
		fprintf ( stderr, " pipe failed \n" );
		exit ( 9 );
	}
	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "pp -fork failed \n" );
			exit ( 9 );
		case 0:
			close ( 1 );
			close ( pfd[0] );
			if ( dup ( pfd[1] ) != 1 ) {
				fprintf ( stderr, "pp - dup failed \n" );
				exit ( 10 );
			}
			execvp ( word1[0], word1 );
			fprintf ( stderr, "pp - no such command %s | %s \n", *word1, word2[0] );
			exit ( 11 );
		default :
			wait ( 0 );
			break;
	 }
	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "pp2 - fork failed \n" );
			exit ( 12 );
		case 0: 
			close ( 0 );
			close ( pfd[1] );
			if ( dup ( pfd[0] ) != 0 ) {
				fprintf ( stderr, "pp2 - dup failed \n" );
				exit ( 13 );
			}
			execvp ( word2[0], word2 );
			fprintf ( stderr, "pp2 - no such command %s | %s \n" , *word1, word2[0]);
			exit ( 14 );
	}
	close ( pfd[0] );
	close ( pfd[1] );
	wait ( 0 );
	return;
}

void func ( )
{
	switch ( fork () ) {
		case -1 :
			fprintf ( stderr, "normal - fork failed \n" );
			exit ( 14 );
		case 0:
			execvp ( word1[0], word1 );
			fprintf ( stderr, "func - no such command %s \n", *word1);
			exit ( 15 );
	}
}

void digifunc ( int num ) {
	int fd;

	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, "fork failed \n" );
			exit ( 16 );
		case 0:
			printf ( "\n <wrod1 - %s>\n", word1 );
			fd = open ( word2[0], O_CREAT |O_TRUNC | O_WRONLY , 0600 );
			if ( fd < 0 ) {
				fprintf ( stderr, "digifunc - open failed\n" );
				exit ( 17 );
			}
			printf ( "fd = %d\n", fd );
			close ( num );
			if ( dup ( fd ) != num ) {
				fprintf ( stderr, "digifunc - dup failed \n" );
				printf ( "%s : \n", strerror(errno) );
				exit ( 18 );
			}
			execvp ( word1[0], word1 );
			fprintf ( stderr, "digifunc - no such command %s %d> %s\n" , *word1,num, word2[0]);
			exit ( 19 );
	}
	return ;
}
