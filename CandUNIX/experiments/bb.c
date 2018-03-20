# include <stdio.h>
# include <stdlib.h>

main() {
	int pipe1[2], pipe2[2];
	const char * ls_args[] = { "ls", NULL };
	const char * wc_args[] = { "wc", NULL };

	pipe (pipe1);
	if ( fork() == 0 ) {
		close (1);
		dup (pipe1[1]);
		close (pipe1[1]);
		close (pipe1[0]);
		execvp ( ls_args[0], ls_args );
	}
	close (pipe1[1]);
	pipe (pipe2);
	if ( fork() == 0 ) {
		close (0);
		dup(pipe1[0]);
		close (pipe1[0]);
		close (1);
		dup(pipe2[1]);
		close (pipe2[1]);
		close (pipe2[0]);
		execvp ( wc_args[0], wc_args );
	}
	close ( pipe2[1] );
	close ( pipe1[0] );
	if ( fork() == 0 ) {
		close (0);
		dup(pipe2[0]);
		close (pipe2[0]);
		execvp ( wc_args[0], wc_args );
	}
	close (pipe2[0]);
	wait ( (int *) 0 );
	wait ( (int *) 0 );
	wait ( (int *) 0 );
	write ( 1, "Job Over\n", 9 );
}
