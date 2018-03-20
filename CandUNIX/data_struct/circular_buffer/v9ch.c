#include <stdio.h>
#include "buffer.h"

#define NITEMS 50

char line[100];
BUFFER *bd;

main()
{
	char ch;
	bd = create_buf (sizeof(ch),NITEMS);
	register char *p;
	if (bd == BUF_FAIL) exit(1);
	while (1)
	{
		printf("\n c<char> to enter R to read E to exit\n");
		if (fgets(line,100,stdin) == NULL)
			exit(2);
		for (p = line; *p == ' ' || *p == '\t'; p++);
		switch (*p)
		{
			
			case 'c':
				if (buf_full(bd)) continue;
				p++;
				ch = *p;
				write_buf (bd,ch);
				break;
			case 'r':
				if (buf_empty(bd)) break;
				read_buf (bd);
				break;
			case 'e':
				while (!buf_empty(bd))
				{
					read_buf (bd);
				}
				destroy_buf(bd);
				exit(0);
		}
	}
}


