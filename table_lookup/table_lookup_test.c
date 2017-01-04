/* 2015-5-5 */


#include <stdio.h>
#include "table_lookup.c"
#include "getword.c"


/* test for table_lookup */

#define MAXWORD 1000

main() {
	struct nlist * np;
	np = hashtable[hash("BAID")];
	np -> name = "BAID";
	np -> defn = "200";	
	np = install("APPL", "700");
	np = install("MSFT", "300");
	np = install("GOOG", "200");


	int c;
	char w[MAXWORD];
	char* w2;
	while ((c = getword(w)) != EOF) 
		if (c == ALP) {
			w2 = sdup(w);	
			if ((c = getword(w)) == EOF) {
				printf("illegal input\n");
				return -1;
			}
			if ((np = install(w2, w)) == NULL) {
				printf("can't install (%s, %s)\n", w2, w);
				return -1;
			}
		}


	int i;
	for (i = 0; i < HASHSIZE; ++i)
		for (np = hashtable[i]; np != NULL; np = np -> next)
			printf("%s, %s", np -> name, np -> defn);

	return 0;
}
