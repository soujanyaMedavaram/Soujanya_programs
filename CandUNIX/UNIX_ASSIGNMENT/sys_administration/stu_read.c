# include <stdio.h>
# include <unistd.h>

main ( ) {
	FILE *fp;
	int Roll_no, phy, che, math;
	char stu_name[25], ch = 'y';

	if ( access ( "student", F_OK ) != 0 )
		fp = fopen ( "student", "w+" );
	else
		fp = fopen ( "student", "a+" );
	while ( ch == 'y' ) {
		printf ( "\n enter student name: " );
		scanf ( "%s", &stu_name );
		fprintf ( fp, "%s   ", stu_name );
		printf ( "\n enter Roll no: " );
		scanf ( "%d", &Roll_no );
		fprintf ( fp, "%5d   ", Roll_no );
		printf ( "\n enter marks\n" );
		printf ( "physics: " );
		scanf ( "%d", &phy );
		fprintf ( fp, "%d   ", phy );
		printf ( "chemistry: " );
		scanf ( "%d", &che );
		fprintf ( fp, "%d   ", che );
		printf ( "mathematics:" );
		scanf ( "%d", &math );
		fprintf ( fp, "%d   \n", math );
		printf ( "do u want to enter one more record(y/n)\n" );
		scanf ( " %c", &ch );
	}
	fclose ( fp );
}
