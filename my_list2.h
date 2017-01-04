/* 2015-5-13 */
/* my_list2.h */


#define MAXLEN 100
typedef char *elementtype;
typedef int position;
typedef struct list {
	/* element[0] for null list */
	elementtype element[MAXLEN + 1];
	position last;
} LIST;

position previous(position p, LIST *Lp); 
position next(position p, LIST *Lp);
position first(LIST *Lp);
position end(LIST *Lp);
position makenull(LIST *Lp);
void delete(position p, LIST *Lp); 
void insert(elementtype x, position p, LIST *Lp); 
position locate(elementtype x, LIST *Lp);
elementtype retrieve(position p, LIST *Lp);
void purge(LIST *L);
