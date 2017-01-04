/* table_lookup.h */

/* 2015-5-4 */

#ifndef TABLE_LOOKUP_H
#define TABLE_LOOKUP_H

struct nlist {
	struct nlist *next;
	char* name;
	char* defn;
};

unsigned hash(char *);
struct nlist* lookup(char *);
struct nlist* install(char*, char*);
void undef(char *);
char *sdup(char *);

#endif
