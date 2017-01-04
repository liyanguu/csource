#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table_lookup.h"


static struct nlist* hashtable[101];

unsigned hash(char* s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; ++s) {
		hashval = *s + 31 * hashval;
	}
	return hashval % 101;
}

struct nlist *lookup(char *s) {
	struct nlist *np;
	
	for(np = hashtable[hash(s)]; np != NULL; np = np -> next)
		if (strcmp(s, np -> name) == 0)
			return np;	return NULL;	}

struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = sdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtable[hashval];
		hashtable[hashval] = np;
	} else
		free((void*) np->defn);
	if ((np->defn = sdup(defn)) == NULL)
		return NULL;
	return np;
}

void undef(char *name) {
	struct nlist *np, *prev = NULL;
	unsigned hashval;

	hashval = hash(name);
	for (np = hashtable[hashval]; np != NULL; np = np->next) {
		if (strcmp(name, np->name) == 0)
			break;
		prev = np;
	}
	if (np != NULL) { if (prev == NULL)  hashtable[hashval] = np->next;
		else     
			prev->next = np->next;
		free((void *) np->name);
		free((void *) np->defn);
		free((void *) np); }
}

char *sdup(char *s) {
	char *p;

	p = (char*) malloc(strlen(s) + 1);	if (p != NULL)
		strcpy(p, s);
	return p;
}
