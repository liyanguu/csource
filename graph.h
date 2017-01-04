#include <stdio.h>
#include <string.h>


#define NSIZE 3
#define GLIMIT 100	/* size limit of a graph */
#define GSIZE 13	/* for use in this program */
typedef enum bool { false, true } bool;

typedef struct vertex {
	bool colored;
	char name[NSIZE];
	int number;
} VERTEX;

typedef struct graph {
	CIRLIST* vertices;
	int size;
	char m[GLIMIT][GLIMIT];
} GRAPH;


void graphInit(GRAPH* G, char* names[], char matrix[][GSIZE]);
bool isAdjcent(int i, int j, GRAPH* G); 
bool isAllColored(GRAPH* G); 
void uncolor(GRAPH *G); 

void cirListInit(CIRLIST* clp); 
void addCirList(VERTEX* vertex, CIRLIST* cl);
int sizeOfCir(CIRLIST* cl); 

LIST listInit(int size);
int addList(VERTEX* vertex, LIST* listptr);
int sizeOfList(LIST* listptr);
void emptyList(LIST* listptr);
void printList(LIST* listptr);

void color(GRAPH* graphptr, LIST q, LIST* listptr); 


