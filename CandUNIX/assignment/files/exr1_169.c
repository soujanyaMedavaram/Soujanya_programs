# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

main ( ) {
	int fd;
	char *buf;
	fd = open ("100kb.data", O_RDONLY );
	while ( read ( fd, buf, 1024 ) > 0 );
	close (fd);
}
