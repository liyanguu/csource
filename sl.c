/*
file name: test_slist.c
log:
	2015-12-4
*/

#include <stdio.h>
#include "slist.h"

main() {
	Sl chapters;

	chapters = listcrt("1. a tutorial introduction");
	listadd(chapters, "2. types, operators, and expressions");
	listadd(chapters, "3. control flow");
	listprt(chapters);
}
