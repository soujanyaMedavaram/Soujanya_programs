# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

main ( int argc, char **argv ) {
	char **cmd = NULL, *line, *token;
	int max, ntk, i;
	FILE *fp;

	switch ( fork ( ) ) {
		case -1:
			fprintf ( stderr, " fork failed \n" );
		case 0:
			*++argv;
			fp = fopen ( *argv, "r" );
			while ( fgets (line, 100, fp ) ) {
				ntk = 0;
				while ( (token = get_word ( line )) ) {
					line = NULL;
					if ( ntk > max ) {
						cmd = realloc ( cmd, (ntk+2) * ( sizeof ( char *) ));
						cmd[ntk] = malloc ( 50 );
					}
					strcpy ( cmd[ntk++], token );
				}
				if ( ntk > max )
					max = ntk;
				cmd[ntk] = NULL;
				execvp ( cmd[0], cmd );
				fprintf ( stderr, " exec failed \n" );
				exit ( 1  );
			}
		default :
			wait ( 0 );
			fclose ( fp );
			for ( i = 0; i <= max; i++ )
				free ( cmd[i] );
			free ( cmd );
			break;
	}
}

			

			
