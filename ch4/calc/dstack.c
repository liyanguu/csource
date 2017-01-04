/* 2015-6-18 */
/*
   dstack.c - pop(), push() a double stack; isempty()
*/

#include <stdio.h>
#include "calc.h"

int sp = 0;
double dstack[DPTH];

double pop() {
	if (sp == 0) {
		printf("stack is empty, can't pop!\n");
		return 0.0;
	}
	else
		return dstack[--sp];
}

void push(double d) {
	if (sp >= DPTH)
		printf("stack is full, can't push!\n");
	else {
		dstack[sp] = d;
		++sp;
	}
}

int isempty() {
	if (sp == 0)
		return 1;
	else
		return 0;
}
