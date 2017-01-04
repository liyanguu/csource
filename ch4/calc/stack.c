#include <stdio.h>

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

double top(void) {
	if (sp <= 0) {
		printf("error: stack empty\n");
		return 0.0;
	} else
		return val[sp - 1];
}

void clear(void) {
	sp = 0;
}

void swap(void) {
	double f1, f2;

	f1 = pop();
	f2 = pop();
	push(f1);
	push(f2);
}
