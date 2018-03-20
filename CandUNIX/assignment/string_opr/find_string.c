# include <stdio.h>
# include <string.h>

int find_string ( char *r, char *s);
void getline(char *line);

main ( ) {
	char *line, *sub_str;
	int ret, i=0;

	line = (char *)malloc(100);
	sub_str = (char *)malloc(50);
	printf ("\n enter the input of strings\n");
	getline(line);
	printf ( "\n enter the string to be searched \n");
	scanf ( " %s", sub_str);
	ret = find_string ( line, sub_str );
	if ( ret == 0 )
		printf ("\n string not found inthe line\n");
	else 
		printf ( "\n string found ");
	exit ( 0 );
}
void getline(char *line) {
	int c, i;
	
	for ( i = 0; i < 1000 && ( c = getchar() ) != EOF  && c != '\n'; i++)
		line[i] = c;
	if ( c == '\n' )
		line[i++] = c;
	line[i] = '\0';
}

int find_string ( char *r, char *s ) {
	char *p;
	int flag = 1;

	p = s;
	while ( *r != '\0' && *p != '\0' ) {
		if ( *r == *p) {
			r++;
			p++;
			flag = 0;
			continue;
		}
		if ( flag == 1)
		r++;
		p = s;
		flag = 1;
	}
	if (*p == '\0')
		return 1;
	 return 0;
}
