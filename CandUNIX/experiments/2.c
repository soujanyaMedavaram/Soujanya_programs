# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

main() {
	int a, ret_val;
	switch (fork()) {

		case -1 :
			printf ("not able to create child process");
			exit (1);

		case 0 :
			execl ("/bin/s", "s", "-l", "2.c", NULL);
			fprintf(stderr, "file is not executed\n");
			exit( 10 );

		default :
			ret_val = wait(&a);
			printf ( "%d->a\n",  WEXITSTATUS ( a ) );
			break;
	}
}

		
