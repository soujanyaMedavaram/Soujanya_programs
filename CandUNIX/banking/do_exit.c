# include <stdio.h>
# include "sb.h"

void do_exit ( int exit_code, char *msg ) {
	fprintf ( stderr, "%s", msg );
	exit ( exit_code );
}
