//	utilities

# include <stdio.h>
# include <stdlib.h>
# include "utils.h"
# include <errno.h>
# include <sys/sem.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <signal.h>

char * get_line ( FILE *fp ) {
	static int len =0;
	static char *line;
	char *p;
	int offset;
# define LEN 20

	if ( fp == NULL ) {
		free ( line );
		return NULL;
	}
	if ( !len ) line = malloc ( len = LEN );
	offset = 0;
	while ( 1 ) {
		if ( fgets ( line + offset, len - offset, fp ) == NULL ) {
			if ( offset ) return line;
			else return NULL;
		}
		if ( line[strlen(line) - 1] != '\n' )
			line = realloc ( line, len += LEN );
		else {
			line[strlen(line) - 1] = '\0' ;
			if ( line[strlen(line) - 1] != '\\' ) {
				if ( line[0] != '\t' || line[0] == '\t') {
				p = line;
					while (isblank( *p ) ) p++;
					if ( *p == '#' || *p == '\n' || *p == '\0')
						return NULL;
				}
				return line;
			}
			line[strlen(line) - 1 ] = ' ' ;
		}
		offset = strlen(line);
	}
}

char * get_word ( char * curr_line ) {
	static char * line;
	static char * word = NULL;
	static int len = 0;
	int k = 0;

	if ( curr_line != NULL )
		line = curr_line;
	if ( len <= strlen (line) )
		word = realloc ( word, strlen(line) + 1 );
	if ( *line == '\0' ) return NULL;
	while ( isblank ( *line ) ) line++;
	if ( *line == '#' || *line == '\n' ) return NULL;
	if ( *line == ':' )
		word[k++] = *line++;
	else while (*line != '\0' && *line != ':' && *line != ' ' && *line != '\t') 
		word[k++] = *line++;
	word[k] = '\0';
	return word;
}

void do_exit ( int exit_code, char *msg ) {
	fprintf ( stderr, "%s\n", msg );
	exit ( exit_code );
}

int create_sem ( int key  ) {
	int semid;

	if ( (semid = semget ( key , 1, 0600 | IPC_CREAT | IPC_EXCL ) ) < 0 )
		return 0;
	if ( semctl ( semid, 0, SETVAL , 1) < 0 )
		return 0;
	return semid;
}

int open_sem ( int key ) {
	int semid;

	if ( (semid = semget ( key , 1, 0600 )) < 0 ) 
		return 0;
	return semid;
}

int rem_sem ( int semid ) {

	if ( semctl ( semid, IPC_RMID, 0 ) == -1 ) {
		return 0;
	}
	return 1;
}

int sem_lock ( int semid ) {
	struct sembuf sops[1]; 

	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = SEM_UNDO;
	if ( semop ( semid , sops, 1 ) < 0 )
		return 0;
	return 1;
}

int sem_unlock ( int semid ) {
	struct sembuf sops[1];

	sops[0].sem_num = 0;
	sops[0].sem_op = 1;
	sops[0].sem_flg = SEM_UNDO;
	if ( semop ( semid, sops, 1 ) < 0 )
		return 0;
	return 1;
}
