typedef struct
{
	int nmax;
	int nchars;
	char *write;
	char *read;
	char *end;
	char buffer[1];
}BUFFER;


# define Nchars		bd->nchars
# define Nmax		bd->nmax
# define Write      bd->write	
# define Read       bd->read
# define End        bd->end
# define Beg        bd->buffer


# define buf_empty(bd)	(Nchars == 0)
# define buf_full(bd)	(Nchars == Nmax)	

# define BUF_SUCCESS	0
# define BUF_FAIL	NULL
# define BUF_FULL	-1
# define BUF_EMPTY	-2

BUFFER * create_buf (int size, int nmax);
int write_buf (BUFFER *bd, char data);
int read_buf (BUFFER *bd);
int destroy_buf (BUFFER *bd);
