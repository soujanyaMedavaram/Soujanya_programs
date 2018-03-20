# include <stdio.h>
# include <unistd.h>

main ( ) {
	char str[20], buf[30];
	printf ( "\n enter a symbolic file name\n" );
	scanf ( "%s", str );
	readlink ( str, buf, sizeof ( str ) );
	buf[sizeof(str)] = '\0';
	printf ( "%s\n", buf );
}
