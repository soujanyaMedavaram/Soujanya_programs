# include <stdio.h>

main () {
	int c;
	while ( c = getchar() != EOF )
		printf ( " c = %d\n", c );
	printf ( "%d - at end c\n", c );
}
