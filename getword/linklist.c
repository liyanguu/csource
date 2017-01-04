#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

struct linklist *lalloc(void) {
	return (struct linklist *) malloc(sizeof(struct linklist));
}

void addlink(struct linklist *lp, int n) {
	for ( ; lp->next != NULL; lp = lp->next)
		;
	if (lp->lnum != n) {
		lp->next = lalloc();
		lp->next->lnum = n;
		lp->next->next = NULL;
	}
}

void linkprint(struct linklist *lp) {
	for ( ; lp != NULL; lp = lp->next)
		printf("%d, ", lp->lnum);
}
