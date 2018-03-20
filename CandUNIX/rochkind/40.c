# include <stdio.h>
# include <errno.h>

main ( ) {
	int amt, fd;
	char *buf;
	if ((amt = read ( fd, buf, 20 ) ) == -1 ) {
		perror ( "hai!");
	}
}
