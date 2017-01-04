/*
file name: slist.h
*/

#define MALLOC(t) (t *)malloc(sizeof(t))

typedef struct node {
	char name[100];
	struct node *next;
} Node; 
typedef Node* Sl;

Sl listcrt(char *name);
Sl listadd(Sl list, char *name);
void listprt(Sl list);
