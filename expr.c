#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"

#define NUMBER '0'

main(int argc, char *argv[]) {
	int cmdtype(char *);
	double op2;

	while (--argc > 0)
		switch(cmdtype(*++argv)) {
		case NUMBER:
			push(atof(*argv));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
			if (op2 == 0.0)
				printf("error: divisor is zero!\n");
			else
				push(pop() / op2);
			break;
		default:
			printf("error: unkown operator %s\n", *argv);
			argc = 0;
			break;
		}
	printf("\t%g\n", pop());
}

int cmdtype(char *s) {
	char d, c = *s;

	if (!isdigit(c) && c != '+' && c != '-')
		return c; 
	if (c == '-' || c == '+') {
		d = c;
		if ((c = *++s) == '\0')
			return d;
	}
	if (isdigit(c))
		return NUMBER;
	return 0;
}
