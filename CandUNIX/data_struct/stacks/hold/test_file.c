# include <stdio.h>

main () {
	FILE *fp, *file_pos;
	long place;
	fpos_t *ptr;
	fp = fopen("file1.dat","a");
	place = ftell(fp);
	printf ("%ld -place\n",place);
	fprintf (fp, "this is a file");
	//fgetpos(file_pos,ptr);
	place = ftell(fp);
	printf ( "%ld - place\n",place);
	fclose(fp);
}

