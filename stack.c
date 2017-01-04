#include <stdio.h>
#include "stack.h"
#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f) {
	if (sp >= MAXVAL)
		printf("error: stack full, can't push %g\n", f);
	else
		val[sp++] = f;
}

double pop(void) {
	if (sp <= 0) {
		printf("error: stack empty\n");
		return 0.0;
	} else
		return val[--sp];
}
