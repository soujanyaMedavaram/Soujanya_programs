# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>

# define BUFSIZE	512

void copy ( char *from, char *to ) {
	int fromfd = -1, tofd = -1, nwrite, n;
	ssize_t nread;
	char buf[BUFSIZE];

	ec_neg1( fromfd = open ( from, O_RDONLY) )
	ec_neg1( tofd = open ( to, O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR) )
	while ( (nread = read ( fromfd, buf, sizeof(buf))) > 0 ) {
		nwrite = 0;
		do {
			ec_neg1 ( n = write(tofd, &buf[nwrite], nread - nwrite ) )
			nwrite += n;
		}while (nwrite < nread );
	}
	if (nread == -1 )
		EC_FAIL
	ec_neg1( close(fromfd) )
	ec_neg1( close(tofd) )
	return;

	EC_CLEANUP_BGN
		(void)close(fromfd);
		(void)close(tofd);
	EC_CLEANUP_END
}

main ( ) {
	char f1[] = "hai", f2[]= "hello";	
	copy ( f1, f2 );
	return 0;
}
