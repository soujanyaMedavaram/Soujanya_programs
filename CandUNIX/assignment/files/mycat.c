# include <stdio.h>
# include <string.h>

void print_file();

int nflag = 0,  eflag = 0, vflag = 0;
int new_line = 0;

main (int argc, char *argv[]) {
	FILE *fp;
	char **walk;
	char *walk2;
	walk = argv;
	while (*++walk) 
		if (**walk == '-') {
			walk2 = *walk;
			while(*++walk2) 
				switch(*walk2) {
					case 'n':
						nflag = 1;
						break;
					case 'e':
						eflag = 1;
						break;
					case 'v':
						vflag = 1;
						break;
					default:
						printf("\n use <man cat> command for help\n");
						exit(1);
				}
		}
	while(*++argv) {
		if (strcmp(*argv, "-") == 0) {
			print_file(stdin);
			new_line = 1;
			fclose(stdin);
			continue;
		}
		else if (**argv == '-')  continue;
		if ((fp = fopen(*argv,"r")) == NULL) {
				printf("file not exist = %s\n",*argv);
				continue;
		}
		print_file(fp);
		fclose(fp);
	}								
	if (argc == 1)
		print_file(stdin);
	exit(0);
}

void print_file(FILE *fp) {
	int c;
	static int i = 1;

	if (nflag == 1 && i == 1)
		printf ("%d  ", i++);
	while ((c = getc(fp)) != EOF) {
		if (c == '\n'|| c == '\t' || c == ' ') {
			if (c == '\n')
				new_line = 1;
			if (eflag == 1 && c == '\n')
				putchar ('$');
			if (vflag == 1) {
				putchar('^');
				putchar(c+0x40);
			}
			else putchar(c);
			continue;
		}
		if (nflag && new_line) {
			printf ("%d  ", i++);
			new_line = 0;
		}
		putchar(c);
	}
}
