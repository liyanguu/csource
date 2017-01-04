/* 
cref.c:
	cross-referencer
log:
	2016-8-10  Exe. 6-3
*/ 

struct linklist {
	int lnum;
	struct linklist *next;
};

struct tnode {
	char *word;
	struct linklist *lines;
	struct tnode *left;
	struct tnode *right;
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword.h"

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

struct tnode *addtreex(struct tnode *, char *, int);
void treexprint(struct tnode *);
struct tnode *talloc(void);
struct linklist *lalloc(void);
void addlist(struct linklist *, int);
void listprint(struct linklist *);
char **bisearch(char **, char *[], int);

main(int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXWORD], *w = word;
	int nline = 1;
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(w[0]) && 
			bisearch(&w, noiseword, NNOISES) == NULL)
			root = addtreex(root, w, nline);
		else if (w[0] == '\n')
			nline++;
	treexprint(root);
	return 0;
}

char **bisearch(char **word, char *tab[], int n) {
	int cond;
	char **low, **high, **mid;

	low = tab;
	high = &tab[n];
	while (low < high) {
		mid = low + (high - low)/2;
		if ((cond = strcmp(*word, *mid)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}

/* add a node with w & line no. n, at or below p */
struct tnode *addtreex(struct tnode *p, char *w, int n) {
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->lines = lalloc();
		p->lines->lnum = n;
		p->lines->next = NULL;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		addlist(p->lines, n);
	else if (cond < 0)
		p->left = addtreex(p->left, w, n);
	else
		p->right = addtreex(p->right, w, n);
	return p;
} 

void treexprint(struct tnode *p) {
	if (p != NULL) {
		treexprint(p->left);
		printf("%s:", p->word);
		listprint(p->lines);
		putchar('\n');
		treexprint(p->right);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct linklist *lalloc(void) {
	return (struct linklist *) malloc(sizeof(struct linklist));
}

void addlist(struct linklist *lp, int n) {
	for ( ; lp->next != NULL; lp = lp->next)
		;
	if (lp->lnum != n) {
		lp->next = lalloc();
		lp->next->lnum = n;
		lp->next->next = NULL;
	}
}

void listprint(struct linklist *lp) {
	for ( ; lp != NULL; lp = lp->next)
		printf("%d ", lp->lnum);
}
