/* 2015-5-10 
	修改了图的节点的数据类型
	练习使用简单循环链表（自己写的）
	穷举所有的着色模式
*/
/* 2015-5-9 整理数据结构及添加其方法

		图结构
			结点数组
			结点数
			关联矩阵
		方法
			是否全部着色
			节点是否相连
*/
			
/* 2015-5-7 big modify
	remove struct graph, using vertex array */
/* 2015-5-6 */
/* DATA STRUCTURE AND ALGORITHM, CHAPTER 1 */
/* greedy.c
	greedy algorithm applies to graph coloring */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* typedefs */
/* ... */

/* function declarations */


main() {
	int i;
	LIST q;
	GRAPH g;
	graphInit(&g, names, matrix);

	LIST newclr = listInit(0);
	for (i = 0, q = g.p; i < g.size; ++i) {
		uncolor(&g);
		while (!isAllColored(&g) {
			color(&g, q, &newclr);
			printList(&newclr);
		} 	 	
		q = q -> next;
		printf("\n\n");
	}

	return 0; 
	
}

/* definition of graph */

#define NSIZE 3
#define GLIMIT 100	/* size limit of a graph */
#define GSIZE 13	/* for use in this program */
typedef enum bool { false, true } bool;

typedef struct vertex {
	bool colored;
	char name[NSIZE];
	int number;
} VERTEX;

	

/* definition of list */


typedef struct cell {
	VERTEX* v;
	struct cell* next;
} CELL;

/***part 1. linked pist**/

typedef CELL *LIST;

/* create an empty list which has size elements */
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




/* test */

/* color - color a graph using greedy algorithm */ 
/* coloring starts from vertex pointed by q */
void color(GRAPH* graphptr, LIST q, LIST* listptr) {
	int i;
	emptyList(listptr);
	for (i = 0; i < graphptr -> size; ++i) {
		if (q -> colored == false) 
			if (!isSetAdjcent(listptr, q -> number, graphptr)) {
				addList(q, listptr);
				q -> colored = true;
			}
		q = q -> next;
	}
}				



/* connection matrix */
/* use char instead of int for small numbers */
char matrix[GSIZE][GSIZE] = {
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
	{1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0},
	{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/* vertices' names */
char* names[] = {
	"ab", "ac", "ad",
	"ba", "bc", "bd",
	"da", "db", "dc",
	"ea", "eb", "ec", "ed", ""};

main() {
	int i;
	LIST q;
	GRAPH g;
	graphInit(&g, names, matrix);

	LIST newclr = listInit(0);
	for (i = 0, q = g.p; i < g.size; ++i) {
		uncolor(&g);
		while (!isAllColored(&g)) {
			color(&g, q, &newclr);
			printList(&newclr);
		} 	 	
		q = q -> next;
		printf("\n\n");
	}

	return 0; 
	
}
	





/*********************************************not use************************************************
 
void g_init (graph* g) { 
	g->vertices =  calloc (GSIZE, sizeof(vertex));	
	g->size = GSIZE;
	int i;
	vertex* v;
	for (i = 0; i < GSIZE; ++i) {
		v = g->vertices + i;
		v->colored = false;
		v->number = i+1;
		strcpy(v->name, names[i]);
		printf("graph initialization:\n");
		printf("%d: %s, %d\n", v->number, v->name, v->colored);
	}
}



bool all_colored(vertex gr[]) {
	int i;
	for (i = 0; i < GSIZE; ++i)
		if (gr[i].colored == false)
			return false;
	return true;
}




typedef struct cell {
	vertex * v;
	struct cell * next;
} CELL;


cell* add(vertex* w, cell* li) {
	cell* temp = li;
	li = (cell *)malloc(sizeof(cell));
	li -> v = w;
	li -> next = temp;
	return li;
}	



bool adjcent(vertex* v, cell* list) {
	cell* p;
	for (p = list; p != NULL; p = p->next)
		if (m[p->v->number - 1][v->number - 1] == 1)
			return true;
	return false;
}



main() {
	vertex g[GSIZE];
	int i;
	for (i = 0; i < GSIZE; ++i) {
		g[i].colored = false;
		strcpy(g[i].name, names[i]);
		g[i].number = i + 1;
		printf("%d: %s, %d\n",
			g[i].number, g[i].name, g[i].colored);
	}
 
	cell* newclr;


	vertex* v;
	cell* p;

	printf("is graph all colored? %d\n", all_colored(g));
	while (!all_colored(g)) {
		newclr = NULL;
		for (i = 0; i < GSIZE; ++i) {
			v = g + i;
			if (v->colored == false && !adjcent(v, newclr)) {
				newclr = add(v, newclr);
				v -> colored = true;
			}	
		}	
		for (p = newclr; p != NULL; p = p -> next)
			printf("%s ", p->v->name);
		printf("\n");
	}

	return 0;
}	


*******************************************************not use****************************************/
