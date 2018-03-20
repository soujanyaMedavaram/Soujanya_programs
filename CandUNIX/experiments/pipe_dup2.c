# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>

main ( ) {
	int pfd[2];
	char **cmd = NULL, **argv = NULL;
	static int i;
	int pipe_active = 0;
	int ntk, j;
	int ncmd = 0, narg = 0;
	char *line, *p, word[20];
	line = malloc ( 100 );

	if ( pipe ( pfd ) != 0 ) {
		fprintf ( stderr, " pipe failed \n" );
		exit ( 1  );
	}
	fgets ( line, 100, stdin );
	for ( p = line; isblank ( *p ); p++ );
	j = 0;
	for ( ; *p != '\0'; p++ ) {
		if ( isblank ( *p ) || *p == '\n' ) {
			word[j] = '\0';
			j = 0;
			argv = realloc ( argv, ( narg + 2 ) * sizeof ( char * ) );
			argv[narg++] = strdup ( word );
			continue;
		}
		word[j++] = *p;
	}
	argv[narg] = NULL;
	i = 0;

	CMD:
	if ( i == narg ) {
		exit ( 0 );
	}
	ntk = 0;
	for ( ; i < narg; ) {
		if ( strcmp ( argv[i] , "|" ) != 0 ) {
			cmd = realloc ( cmd, (ntk + 2 )* sizeof ( char * ) );
			cmd[ntk++] = strdup ( argv[i] );
			i++;
		}
		else if ( !strcmp ( argv[i], "|" ) ) { 
			pipe_active += 2 ; 
			i++;
			break; 
		}
	}
	if ( i == narg ) pipe_active = 1;
	cmd[ntk] = NULL;
	ncmd++;
	switch ( fork ( ) ) {
		case -1 :
			fprintf ( stderr, " fork failed \n" );
			exit ( 1 );
		case 0 :
		printf ( "pipe %d ncmd %d\n", pipe_active, ncmd );
			if ( pipe_active == 2 ) {
				if ( dup2 ( pfd[1] , 1 ) != 1 ) {
					fprintf ( stderr, " dup1 failed \n" );
					exit ( 1  );
				}
				close ( pfd[1] );
				close ( pfd[0] );
			}
			else if ( pipe_active == 1 ) {
				if ( dup2 ( pfd[0], 0 ) != 0 ) {
					fprintf ( stderr, "dup2 failed \n" );
					exit ( 2 );
				}
				close ( pfd[0] );
				close ( pfd[1] );
			}
			else if ( pipe_active > 2 ) {
				if ( dup2 ( pfd[0], 0 ) != 0 ) {
					fprintf ( stderr, "dup3 failed\n" );
					exit ( 3  );
				}
				close ( pfd[0] );
				if ( dup2 ( pfd[1], 1 ) !=  1 ) {
					fprintf ( stderr, "dup4 failed \n" );
					exit ( 4 );
				}
				close ( pfd[1] );
			}
			fprintf ( stderr, " BEFORE EXECVP \n" );
			execvp ( cmd[0], cmd );
			fprintf ( stderr, " exec failed \n" );
			exit ( 8 );
		default :
//			if ( pipe_active > 1 ) 
//				wait ( 0 );
				//while ( --ncmd )

			if ( pipe_active == 1 ) {
				close ( pfd[1] );
				close ( pfd[0] );
			}
			for ( j =0; j <= ntk; j++ )
				free ( cmd[j] );
			free ( cmd );
			cmd = NULL;
			if ( i != narg )
				goto CMD;
	}
}


			
			
	
