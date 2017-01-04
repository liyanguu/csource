/* count.c:
	print the distinct words into decreasing order of 
	frequency of occurrence.
log: 
	8-11 Exe 6-4     
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword.h"
#include "linklist.h"

struct tnode {
	char *word;
	int count;
	int match;
	struct linklist *indx;
	struct tnode *left;
	struct tnode *right;
};

char *noiseword[] = {
	"a",
	"an",
	"and",
	"are",
	"in",
	"is",
	"of",
	"or",
	"that",
	"the",
	"this",
	"to"
};

#define MAXWORD 100
#define NNOISES (sizeof noiseword / sizeof noiseword[0])
#define NDISTINCT 1000

struct tnode *addtree(struct tnode *, char *, int, int);
void treeprint(struct tnode *);
struct tnode *talloc(void);
int treestore(struct tnode *, struct tnode **, int, int);
void listprint(struct tnode **, int);
void quicksort(void *[], int, int, int (*)(void *, void *));
int compare(struct tnode *, struct tnode *);
char **bisearch(char **, char *[], int);

int bycount, cross, group, nidnt = 6;
struct tnode *list[NDISTINCT];

main(int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXWORD];
	char *w = word;
	int c, ndist, lineno;

	while (--argc > 0 && (*++argv)[0] == '-') {
		if (isdigit((*argv)[1])) {
			nidnt = atoi(++*argv);
			continue;
		}
		while (c = *++argv[0])
			switch(c) {
			case 'n':
				bycount = 1;
				break;
			case 'f':
				cross = 1;
				break;
			case 'g':
				group = 1;
				break;
			default:
				argc = 0;
				break;
			}
	}
	if (argc < 0) {
		printf("usage: count -nfg\n");
		exit(1);
	}
	
	root = NULL;
	lineno = 1;
	while ((c = getword(word, MAXWORD)) != EOF) {
		if (c == '\n')
			lineno++;
		if (isalpha(word[0])
		&& bisearch(&w, noiseword, NNOISES) == NULL)
			root = addtree(root, word, lineno, 0);
	}

	if (bycount) {
		ndist = treestore(root, list, 0, NDISTINCT);
		quicksort((void **) list, 0, ndist-1,
			(int (*)(void *, void*)) compare);
		listprint(list, ndist);
	} else
		treeprint(root);

	exit(0);
}

int treestore(struct tnode *p, struct tnode **list, 
		int n, int maxnode) {

	if (p != NULL) {
		n = treestore(p->left, list, n, maxnode);
		if (n < maxnode)
			list[n++] = p;
		n = treestore(p->right, list, n, maxnode);
	}
	return n;
}

void listprint(struct tnode **list, int n) {
	struct tnode *p;

	while (n-- > 0) {
		p = *list++;
		printf("%s: %d\n", p->word, p->count);
	}
}

int compare(struct tnode *p, struct tnode *q) {
	return p->count - q->count;
}

/* add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int ln, int found) {
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->match = found;
		p->indx = lalloc();
		p->indx->lnum = ln;
		p->indx->next = NULL;
		p->left = p->right = NULL;
	} else {
		cond = strcmp(w, p->word);
		if (strncmp(w, p->word, nidnt) == 0 && cond != 0) {
			p->match = 1;
			found = 1;
		}
		if (cond == 0) {
			p->count++;
			addlink(p->indx, ln);
		} else if (cond < 0)
			p->left = addtree(p->left, w, ln, found);
		else
			p->right = addtree(p->right, w, ln, found);
	}
	return p;
} 

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		if (group) {
			if (p->match == 1)
				printf("%s\n", p->word);
		} else {
			printf("%s: ", p->word);
			if (cross)
				linkprint(p->indx);
			printf("%d\n", p->count);
		}
		treeprint(p->right);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}
