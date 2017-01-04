/* 
match.c         
2016-8-9  copied from P140
     8-10 Exe 6-2     
*/

struct tnode {
	char *word;
	int match;          /* match found */
	struct tnode *left;
	struct tnode *right;
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword.h"

#define MAXWORD 100
struct tnode *addtreex(struct tnode *, char *, int, int);
void treexprint(struct tnode *);
struct tnode *talloc(void);

main(int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXWORD];
	int num;   /* #first ident. chars */
	
	num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0]+1) : 6;
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && strlen(word) >= num)	
			root = addtreex(root, word, num, 0);
	treexprint(root);
	return 0;
}

/* addtreex: add a distinct node with found = 1 if match 
	in first num chars, or with found = 0 otherwise, 
	at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int num, int found) {
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->match = found;
		p->left = p->right = NULL;
	} else if (cond = strcmp(w, p->word)) {    /* distinct node */
		if (strncmp(w, p->word, num) == 0) /* found a match */
			found = p->match = 1;
		if (cond < 0)
			p->left = addtreex(p->left, w, num, found);
		else
			p->right = addtreex(p->right, w, num, found);
	}
	return p;
}

/* treexprint: in-order print of tree p if p->match = 1 */
void treexprint(struct tnode *p) {
	if (p != NULL) {
		treexprint(p->left);
		if (p->match)
			printf("%s\n", p->word);
		treexprint(p->right);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}
