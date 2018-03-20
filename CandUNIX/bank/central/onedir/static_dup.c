# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "selection.h"

# define MAX_LINE	100
# define CONF_SB	"config"

int max_channel ( ) {
	int max_chl = 0, count;
	char line[MAX_LINE];
	char *p;
	FILE *fp;

	fp = fopen ( CONF_SB, "r" );
	if ( fp == NULL ) {
		fprintf ( stderr, "Can not open configuration file\n" );
		return -1;
	}
	while ( fgets ( line, MAX_LINE, fp ) ) {
		for ( p = line; isblank ( *p ); p++ ) ;
		if ( *p == '#' || *p == '\n' ) continue;
		while ( !isblank ( *p ) ) p++;
		while ( isblank ( *p ) ) p++;
		count = atoi ( p );
		if ( count > max_chl ) max_chl = count;
	}
	fclose ( fp );
	return max_chl;
}

int curr_channel ( ) {
	int found = 0, i;
	char tty_name[MAX_LINE];
	char line[MAX_LINE];
	char *p;
	FILE *fp;

	fp = fopen ( CONF_SB, "r" );
	if ( fp == NULL ) {
		fprintf ( stderr, "Cannot open config file\n" );
		return -1;
	}
	while ( fgets ( line, MAX_LINE, fp ) != NULL ) {
		for ( p = line; isblank ( *p ); p++ ) ;
		if ( *p == '#' || *p == '\n' ) continue;
		for ( i = 0; !isblank ( *p ); p++, i++ )
			tty_name[i] = *p;
		tty_name[i] = '\0';
		if ( !strcmp ( ttyname ( 0 ), tty_name ) ) {
			found = 1;
			break;
		}
	}
	if ( !found ) return -1;
	while ( isblank ( *p ) ) p++;
	fclose ( fp );
	return atoi ( p );
}

int dynamic_selection ( void ) {
	return 0;
}
