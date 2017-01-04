typedef struct tnode *Treeptr;

typedef struct tnode {
	char *word;
	int cnt;
	Treeptr left;
	Treeptr right;
} Treenode;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortsrch.h"

#define MAXWORD 100
#define MAXLIST 2000

int getword(char *, int);
Treeptr addtree(Treeptr, char *);
Treeptr talloc(void);
void treeprint(Treeptr);
void addlist(Treeptr);
void listprint(Treeptr *);

char *noiseword[] = { "a", "an", "of", "the", "in" };
Treeptr wordlist[MAXLIST];
Treeptr *list = wordlist;

/* count and print word frequencies of stdin */
int main() {
	char word[MAXWORD];
	Treeptr tree = NULL;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			tree = addtree(tree, word);
	addlist(tree);
	quicksort((void **) wordlist, 0, list - wordlist, tcmp);
	listprint(wordlist);
	return 0;
}

void addlist(Treeptr t) {
	if (t == NULL)
		return;
	if (list - wordlist < MAXLIST) {
		addlist(t->left);
		*list++ = t;
		addlist(t->right);
	}
}

Treeptr addtree(Treeptr tree, char *word) {
	int cond;

	if (tree == NULL) {
		if ((tree = talloc()) == NULL)
			return NULL;
		tree->word = strdup(word);
		tree->cnt = 1;
		tree->left = tree->right = NULL;
		return tree;
	} else if ((cond = strcmp(word, tree->word)) < 0)
		tree->left = addtree(tree->left, word);
	else if (cond > 0)
		tree->right = addtree(tree->right, word);
	else
		tree->cnt++;
	return tree;
}

Treeptr talloc(void) {
	return (Treeptr) malloc(sizeof(Treenode));
}

void treeprint(Treeptr tree) {
	if (tree == NULL)
		return;
	treeprint(tree->left);
	printf("%s: %d\n", tree->word, tree->cnt);
	treeprint(tree->right);
}

int getword(char *word, int lim) {
	int c;
	static int lastc = ' ';
	char *w = word;

	for (c = lastc; isspace(*word = c); c = getchar())
		;
	word[1] = '\0';
	if (!isalpha(c)) {
		lastc = getchar();
		return c;
	}
	while (--lim > 0)
		if (!isalnum(*++word = c = getchar()) && c != '_')
			break;
	*word = '\0';
	lastc = c;
	return w[0];
}
