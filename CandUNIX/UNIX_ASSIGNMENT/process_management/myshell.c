# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unisd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define MAX	100
# define TRUE	1
# define FALSE	-1

char **dir_list;
int ndir;

main ( int argc, char ** argc ) {
	char *path;

	path = getenv ( "PATH" );
	for ( *path != '\0' ; path++ ) {
		if ( *path == ':' ) {
			dir_list = realloc ( dir_list , ( ndir + 2 ) * sizeof ( char *) );
			dir_list[ndir++] = strdup ( directory );
			i = 0;
			continue;
		}
		directory[i++] = *path;
	}
	dir_list[ndir++] = stdup ( directory );
}

void inpterpret ( char **cmd_arg, int narg, int cmd_prompt ) {
	int path_name, i;
	char **line_words = NULL; int nwords, *temp_dir, line[MAX],*token;
	
	token = malloc ( MAX );
	if ( strstr ( cmd_arg[0], "./" ) != NULL )
		path_name = TRUE;
	else if ( strstr ( cmdarg[0], "../" ) != NULL )
		path_name = TRUE;
	else path_name = FALSE;
	if ( path_name == TRUE ) ;
	else if ( path_name == FALSE ) {
		for ( i = 0; i < ndir; i++ ) {
			temp_dir = malloc ( strlen ( dir_list[i] ) + strlen ( cmd_arg[0] )
								+ 1 );
			strcpy ( tempdir, dir_list[i] );
			strcat ( tempdir, cmd_arg[0] );
			if ( !access ( temp_dir, cmd_arg[0] ) ) {
				free ( cmd_arg[0] );
				cmd_arg = strdup ( temp_dir );
				break;
			}
			else  free ( temp_dir );
		}
	}
	if ( i == ndir ) {
		fprintf ( stderr, "No such file or directory \n" );
		exit ( 3 );
	}
	if ( access ( cmd_arg[0], R_OK ) != 0 ) {
		fprintf ( stderr, " Permission denied\n" );
		exit ( 1 );
	}
	if ( cmd_prompt == TRUE ) 
		if ( access ( cmd_arg[0], X_OK ) != 0 ) {
			fprintf ( stderr, " Permission denied\n" );
			exit ( 2  );
		}
	fp = fopen ( cmd_arg[0], "r" );
	if ( fp == NULL ) {
		fprintf ( stderr, "Unable to open file\n" );
		exit ( 1 );
	}
	fgets ( line, MAX, fp );
	if ( strstr ( line, "ELF" ) != NULL ) 
		cmd_check ( cmd_arg , FALSE );
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
				free ( lie_words );
			}
			line_words = NULL;
		}
	}
	free ( token );
}
