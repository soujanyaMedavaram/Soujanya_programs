file_exec ( FILE *fp ) {
	int nwords =0;
	int m = -1;
	while ( 1 ) {
		if ( nwords )
		m = nwords;
		pp = 0;
		printf ( "sou>" );
		while ( getword ( line, fp ) != NULL ) {
			if ( line == "|" ) {
				pp++;
				commd_exe ( word1, NULL, pp );
			}
			if ( line == ">" || line == " <" ) {
				flag = 1;
				if ( getword ( line,fp ) != NULL ) {
					word2 = realloc ( word2, sizeof(char *) );
					word2[0] = strdup ( line );
					word2[1] = NULL;
				}
				commd_exec ( word1, word2, pp );
			}
			if ( nwords > m ) {
				nwords++;
				word1 = ralloc ( wrod1, sizeof ( char *) * nwords );
				word1[nwords - 1 ] = strdup ( line );
				word1[nowrds] = NULL;
			}
			if ( pp >1 )
				commd_exe ( NULL, NULL, pp );
		}
		if ( flag = 0 )
			commd_exec ( word1, NULL, pp );
}

void commd_exe ( char **word1, char **word2, int pp ) {
	if ( word1 and word2 == NULL && pp > 1 ) {
		close ( pfd[1]);
		close( pfd[0] );
		wait ( 0 );
	}
	switch ( fork () ) {
		case -1: fpritfn (
