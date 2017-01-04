#include "graph.h"

typedef CELL *LIST;

/* create an empty list which has size elements */


void creatList(LIST* plist) {
	*plist = NULL;
	addList(NULL, plist);
}

LIST listInit(int size) {
	LIST list = NULL;
	while (size--)
		addList(NULL, &list);
	return list;
}


int addList(VERTEX* vertex, LIST* listptr) {
	CELL* p = *listptr;
	if ((*listptr = (LIST)malloc(sizeof(CELL))) == NULL)
		return 0;
	(*listptr) -> next = p;
	(*listptr) -> v = vertex;
	return 1;
} 


int sizeOfList(LIST* listptr) {
	int i;
	for (i = 0; *listptr != NULL; *listptr = (*listptr) -> next)
		++i;
	return i;
}

void emptyList(LIST* listptr) {
	CELL *p, *q;
	for (p = *listptr; p != NULL; p = q) {
		q = p -> next;
		free(p);
	}	
	*listptr = NULL;
}

void printList(LIST* listptr) {
	CELL *p = *listptr;
	for ( ; p != NULL; p = p -> next)
		printf("%s ", p -> v -> name);
	printf("\n");
}


/** part2. circle list **/


typedef struct cirlist {
	int listSize;
	LIST p;
} CIRLIST;

/* initializing a list */
void cirListInit(CIRLIST* clp) {
	clp -> listSize = 0;
	clp -> LIST = NULL;
}

void addCirList(VERTEX* vertex, CIRLIST* cl) {
	if (cl -> p == NULL) {	/* add first vertex */
		cl -> p = (LIST)malloc(sizeof(CELL));
		cl -> p -> next = cl -> p;
	}
	else {			/* add vertex in front */
		LIST temp = cl -> p -> next;
		cl -> p = cl -> p -> next = (LIST)malloc(sizeof(CELL));
		cl -> p -> next = temp;
	}

	cl -> p -> v = (VERTEX* )malloc(sizsof(VERTEX));
	strcpy(cl -> p -> v -> name, vertex -> name);
	cl -> p -> v -> colored = vertex -> colored;
	cl -> p -> v -> number = vertex -> number;

	cl -> listSize += 1;
}
	
int sizeOfCir(CIRLIST* cl) {
	return cl -> size;
}

	
/* definition of graph */
/* use a circle list to hold vertices */

typedef struct graph {
	CIRLIST* vertices;
	int size;
	char m[GLIMIT][GLIMIT];
} GRAPH;

/* creat a graph according to string array names */
/* e.g. char* names[] = {"name1", "name2", ... , ""};
	there is a zero sting marks the end. */
/* the matrix's size must be consistent with that of names */
void graphInit(GRAPH* G, char* names[], char matrix[][GSIZE]) {
	printf("graph initializing:\n");
	int i, j;
	VERTEX vertex;
	cirListInit(G -> vertices);
	for (i = 0; strcmp(names[i], ""); i++) {
		strcpy(vertex.name, names[i]);
		vertex.number = i + 1;
		vertex.colored == false;
		addCirList(*vertex, G -> vertices);
		printf("%s\n", G -> vertices -> p -> v -> name);
	}			
	
	G -> size = i;
	printf("graph size is: %d\nconnection matrix:\n", G -> size);

	for (i = 0; i < G -> size; ++i) {
		for (j = 0; j < G -> size; ++j) { 
			G -> m[i][j] = matrix[i][j];
			printf("%d ", G -> m[i][j]);
		}
		printf("\n");
	}
}

/* if vertex number i is adjcent with vertex number j in graph G */
bool isAdjcent(int i, int j, GRAPH* G) {
	return G -> m[i-1][j-1] == 1 ? true : false;
}


bool isAllColored(GRAPH* G) {
	int i;
	LIST q;
	for (i = 0, q = G -> vertices -> p; i < G -> size; ++i) {
		if (G -> q -> v -> colored == false)
			return false;
		q = q -> next;
	}
	return true;
}

void uncolor(GRAPH *G) {
	int i;
	LIST q;
	for (i = 0, q = G -> vertices -> p; i < G -> size; ++i) {
		q -> v -> colored = false;
		q = q -> next;
	}
}


/* if vertex number i is adjcent with a partial set of graph G */
bool isSetAdjcent(LIST* listptr, int i, GRAPH* G) {
	CELL *p;
	for(p = *listptr; p != NULL; p = p -> next)
		if (isAdjcent(G -> vertices -> p -> v -> number, p -> v -> number, G))
			return true;
	return false;
}
