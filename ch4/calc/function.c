#include <stdio.h>
#include <math.h>
#include <string.h>
#include "calc.h"

void mathfnc(char *s) {
	double op2;

	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "pow") == 0) {
		op2 = pop();
		push(pow(pop(), op2));
	} else
		printf("error: unknow function %s\n", s);
}
