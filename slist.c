/*
file name: sl.c - simple list methods
change log:
	2015-12-4 create: 实现链表的创建与遍历。
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

Sl listcrt(char *name) {
	Sl head;
	
	head = MALLOC(Node);
	strcpy(head->name, name);
	head->next = NULL;
	return head;
}

Sl listadd(Sl list, char *name) {
	Sl tmp;

	for (tmp = list; tmp->next != NULL; tmp = tmp->next)
		;
	tmp->next = listcrt(name);
	return list;
}

void listprt(Sl list) {
	while (list != NULL) {
		printf("%s\n", list->name);
		list = list->next;
	}
}
