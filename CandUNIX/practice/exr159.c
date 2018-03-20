# include <stdio.h>
# define MAX	100
main ( ) {
	int day, i, c, year;
	char month[20] = {0}, s[MAX];
	int mnth;

	day = year = mnth = 0;
	printf ("enter date month and year \n");
	for ( i = 0; i < MAX , ( c = getchar() ) != EOF && c != '\n'; i++ ) 
		s[i] = c;
	s[i] = '\0';
	if ( sscanf ( s, "%d %s %d", &day, month, &year ) == 3 )
		printf ("Date: %d %s %d\n", day, month, year );
	else if ( sscanf ( s, "%d/%d/%d", &day, &mnth, &year ) == 3 )
		printf ( "Date: %d/%d/%d\n", day, mnth, year );
	else printf ("\n %d - %d - %d worng format \n", day, mnth, year );
}


		
