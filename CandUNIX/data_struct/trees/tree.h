struct node {
	struct node *left;
	struct node *right;
	char data[1];
};

typedef struct {
	struct node *root;
	char *new;
	char *pos;
	int new_added;
	int size;
	unsigned long path;
	int height;
	int (*compare) ();
	char *array;
}TREE;

TREE *open_tree (int size, int (*compare) () );
int close_tree (register TREE *td);
int free_tree (struct node * node );
int add_leaf (register TREE *td, char *new);
int how_many (struct node *node);
int navigate (register TREE *td, void (*action) (), void *app_data);
void traverse (struct node *node, void (*action) (), void *app_data);
void place_leaf (char *new, void *td);
int nleaves (register TREE *td);
struct node * array_to_tree (char *array, int size, int n, int *pcounter);
int read_first (register TREE *td, char *data);
int read_next (register TREE *td, char *data);

# define T_SUCCESS 0
# define T_NO_MORE 1
# define T_FAIL NULL

# define Root td -> root
# define New td -> new
# define Pos td -> pos
# define Size td -> size
# define Compare td -> compare
# define Array td -> array
# define New_added td -> new_added
# define Left node -> left
# define Right node -> right
# define Data node -> data
# define Path td -> path
# define Height td -> height
