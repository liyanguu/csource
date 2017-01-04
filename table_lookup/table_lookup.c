/* table_lookup.c - P143 */

/* 2015-5-4 */

/* contains:
	hash() - generate hash value for string s ;
	install() - put (name, defn) into hash table ;
	lookup() - look for string s in hash table ;
	sdup() - duplicate string s ;
*/
	

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table_lookup.h"

#define HASHSIZE 101

static struct nlist* hashtable[HASHSIZE];

/* hash: form hash value for string s */
unsigned hash(char* s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; ++s) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

/* lookup: look for s in a hashtable */
struct nlist *lookup(char *s) {
	struct nlist *np;
	
	for(np = hashtable[hash(s)]; np != NULL; np = np -> next)
		if (strcmp(s, np -> name) == 0)
			return np;	/* FOUND */
	return NULL;	/* NOT FOUND */
}

/* install: put (name, defn) pair in hashtable */
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
	if (np != NULL) { /* found name */
		if (prev == NULL)  /* first in the hash list ? */
			hashtable[hashval] = np->next;
		else     
			prev->next = np->next;
		free((void *) np->name);
		free((void *) np->defn);
		free((void *) np); /* free structure */
	}
}

/* sdup: make a duplicate of string s */
char *sdup(char *s) {
	char *p;

	p = (char*) malloc(strlen(s) + 1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}
