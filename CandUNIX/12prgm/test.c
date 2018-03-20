# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

main ( ) {
	printf ( "%d\n", WTERMSIG ( 129 ) );
}
