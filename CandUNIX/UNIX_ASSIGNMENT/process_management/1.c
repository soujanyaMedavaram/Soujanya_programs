# include <stdio.h>

main ( ) {
//	setbuf ( stdout, NULL );
	printf ( "%d:%d\n", getpid ( ), getppid ( ) );
	fflush ( stdout );
	fork ( );
	printf ( "%d:%d\n", getpid ( ), getppid ( ) );
	fflush ( stdout );
	fork ( );
	printf ( "%d:%d\n", getpid ( ), getppid ( ) );
	fflush ( stdout );
	fork ( );
	printf (  "%d:%d\n", getpid ( ), getppid ( ) );
	fflush ( stdout );
}

// we can use the fflush to give same result as 'setbuf' gives
