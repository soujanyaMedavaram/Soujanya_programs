#include <stdio.h>
#include "buffer.h"

#define NITEMS 5

char line[100];
BUFFER *bd;

main()
{
	int num;	
	bd = create_buf (sizeof(num),NITEMS);
	register char *p;
	if (bd == BUF_FAIL) exit(1);
	while (1)
	{
		printf("\n o<num> to enter R to read E to exit\n");
		if (fgets(line,100,stdin) == NULL)
			exit(2);
		for (p = line; *p == ' ' || *p == '\t'; p++);
		switch (*p)
		{
			
			case 'o':
				if (buf_full(bd)) continue;
				p++;
				num = atoi(p);
				write_buf (bd,num);
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


