# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char **dir_list;
int ndir;

main  ( ) {
	/*char * res, *p;
	int count = 0;

	res = getenv ( "PATH" );
	p = res;
	while ( *p ) { p++; count++; }
	*(res + count) = ':' ;
	printf ( "%s\n", res );*/

	char *path , directory[20];
	int i = 0;

	dir_list = NULL;
	path = getenv ( "PATH" );
	printf ( " %s\n", path );
	for ( ;*path != '\0' ; path++ ) {
		if ( *path == ':' ) {
		printf ( " paht = : <%c>\n", *path );
			directory[i] = '\0';
			dir_list = realloc ( dir_list , ( ndir + 2 ) * sizeof ( char *) );
			dir_list[ndir++] = strdup ( directory );
			i = 0;
			continue;
		}
		directory[i++] = *path;
	}
	directory[i] = '\0';
	dir_list[ndir] = strdup ( directory );
	//dir_list[ndir] = NULL;
	printf ( " before printf\n" );
	for ( i =0; i < ndir; i++ )
		printf ( "<%s>\n", dir_list[i] );
}
