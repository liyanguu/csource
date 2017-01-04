typedef struct tnode *Treeptr;

typedef struct tnode {	/* the tree node */
	char *name;	/* points to the text */
	int count;	/* number of occurence */
	Treeptr left;	/* left child */
	Treeptr right;	/* right child */
} Treenode;

Treeptr talloc(void);
