# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

main ( ) {
	printf ( "O_RDONLY %d\n", O_RDONLY );
	printf ( "O_WRONLY %d\n", O_WRONLY );
	printf ( "O_RDWR %d\n", O_RDWR );
}

