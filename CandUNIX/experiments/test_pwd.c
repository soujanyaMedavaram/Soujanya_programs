# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <pwd.h>

int main ( ) {

	struct passwd *pwd;
	pwd = getpwuid ( getuid ( ) );
	printf ( "%s\n", pwd->pw_passwd );
	printf ( "%s\n", pwd->pw_name );
	return 0;
}
