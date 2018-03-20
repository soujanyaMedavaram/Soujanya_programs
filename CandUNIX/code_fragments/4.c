 # include <stdio.h>

void * x (void *p1, void *p2)
{
	void *t = p2;
	while(*p2++ = *p1++);
	return t;
}
 main()
 {
 	char *s, *d;
	strcpy(s,"hello");
	x(s,d);
}

