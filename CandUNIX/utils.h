//	utils.h
# ifndef _UTILS_H
#define _UITLS_H

void do_exit ( int exit_code, char * msg );
char * get_line ( FILE * fp );
char * get_word ( char * curr_line );
int create_sem ( int key ) ;
int open_sem ( int key ) ;
int rem_sem ( int semid ) ;
int sem_lock ( int semid ) ;
int sem_unlock ( int semid ) ;

# endif //_UTILS_H
