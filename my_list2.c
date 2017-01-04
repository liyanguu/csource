/* 2015-5-13 */
/* Array Implementation of List P41 */
/* implementation of my_list2.h */

#include <stdio.h>
#include <string.h>
#include "my_list2.h"

/* previous() and next() gaurantee the returned position is correct */
/* return a position previous to the current position p of LIST L, 1 if p <= 1 */	
position previous(position p, LIST *Lp) {
	return p <= 1 ? 1 : p - 1;
} /* previous */

/* returns the next position, end(L) if last position */
position next(position p, LIST *Lp) { return p >= Lp->last ? end(Lp) : p + 1; } /* next */

/* return 1, if L is empty, return end(L) */
position first(LIST *Lp) {
	return Lp->last == 0 ? end(Lp) : 1; 
} /* first */ 

/* returns the position next to L's last element */
position end(LIST *Lp) {
	return Lp->last + 1;	/* why: for covenient in loop; for locate() */
} /* end */

/* makes L a empty list, returns end(L) */
position makenull(LIST *Lp) {
	Lp->last = 0;
	return end(Lp);
} /* makenull */


/* mine 
void insert(position p, elementtype elem, LIST list) {
	position i;
	if (p < 1 || p > list.last) {
		printf("bad position: %d.", p);
		return;
	}
	if (end(list) >= MAXLEN + 1) {
		printf("list is full, can't insert!\n");
		return;
	}
	for (i = list.last; i >= p; --i)	
		list.element[i + 1] = list.element[i];
	list.element[p] = elem;
	list.last++;
}			
*/


/* insert and delete should use with correct position p */
/* insert element x to position p (include the end(L) position) in L */
void insert(elementtype x, position p, LIST *Lp) {
	if (Lp->last >= MAXLEN)
		printf("error: list is full, can't insert!\n");
	else {
		position i;
		for (i = Lp->last; i >= p; i--)
		/* shift elements follow element[p] included down one position */
			Lp->element[i + 1] = Lp->element[i];
		Lp->last++;
		Lp->element[p] = x;
	}
} /* insert */ 

/* deletes element in position p */
void delete(position p, LIST *Lp) {
	Lp->last--;
	position i;
	for ( ; p <= Lp->last; ++p)
		Lp->element[p] = Lp->element[p + 1];	
} /* delete */
	
/* returns the position of element x in L, end(L) if x doesn't exist */
position locate(elementtype x, LIST *Lp) {
	position p;
	for (p = 1; p <= Lp->last; ++p)
		if (Lp->element[p] == x)
			return p;
	return Lp->last + 1;	/* not found */
} /* locate */

/* returns the element value of position p */
elementtype retrieve(position p, LIST *Lp) { return Lp->element[p]; } /* retrieve */

void purge(LIST *Lp) {
	position p, q;
	p = first(Lp);
	while (p < end(Lp)) {
		q = next(p, Lp);
		while (q < end(Lp)) {
			if (strcmp(Lp->element[q], Lp->element[p]) == 0)
				delete(q, Lp);
			else
				q = next(q, Lp);
		}
		p = next(p, Lp);
	}
}	
