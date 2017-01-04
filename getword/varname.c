#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
	char *word;
	int match;
	struct tnode *left;
	struct tnode *right;
}

#define MAXWORD   100
#define YES       1
#define NO        0
#define MAXCHAR   6       /* number of first ident. chars */

struct tnode *addtreex(struct tnode *, char *, int, int *);
void treexprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
int compare(char *, struct tnode *, int, int *);

main() {
	struct tnode *root;
	char word[MAXWORD+1];
	int found = NO;         /* YES if match was found */
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]) && strlen(word) >= MAXCHAR)
			root = addtreex(root, word, MAXCHAR, &found);
		found = NO;
	}
	treexprint(root);
	return 0;
}

/* addtreex: add a node with w, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int num, int *found) {
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->match = *found;
		p->left = p->right = NULL;
	} else if ((cond = compare(w, p, num, found)) < 0)
		p->left = addtreex(p->left, w, num, found);
	else if (cond > 0)
		p->right = addtreex(p->right, w, num, found);
	return p;
}

