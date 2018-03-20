# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

int main ( int argc, char ** argv ) {
	int val;

	while ( *++argv ) {
		val = atoi ( *argv );
		if (WIFEXITED (val) )
			 printf ( "exit code = %d\n", WEXITSTATUS (val) );
		else printf ( "signal no.= %d\n", WTERMSIG (val) );
	}
}
