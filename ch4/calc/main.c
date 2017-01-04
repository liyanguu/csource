/*
main.c - main function for reverse polish calculator get commnad; 
	identify command and calculate;

log:
	 2015-6-18 * 
	 2016-8-29 11:10 a.m. scanf version */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h>
#include "calc.h"

#define MAXOP 100
#define MAXVAR 26
double varbuf[MAXVAR];

int main() {
	int type, var, cmdtype, i;
	double op2, v;
	char cmd[MAXOP];

	for (i = 0; i < MAXVAR; ++i)
		varbuf[i] = 0.0;
	printf("> ");
	while ((type = getop(cmd)) != EOF) {
		switch(type) {
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
		case '%':
			op2 = pop();
			if (op2 <= 0)
				printf("error: invalid modulus %g!\n", op2);
			else
				push((int) pop() % (int) op2);
			break;
		case NUMBER:
			sscanf(cmd, "%lf", &op2);
			push(op2);
			break;
		case '=':
			pop();
			varbuf[var - 'A'] = pop();
			break;
		case VAR:
			push(varbuf[(var = *cmd) - 'A']);
			break;
		case 'v':
			push(v);
			break;
		case NAME:
			mathfnc(cmd);
			break;
		case 't':
			printf("\t%.8g\n", v = top());
			break;
		case 's':
			swap();
			break;
		case 'd':
			push(top());
			break;
		case 'c':
			clear();
			break;
		case '\n':
			if (cmdtype == '=')
				printf("\t%c = %.8g\n", var, varbuf[var-'A']);
			else
				printf("\t%.8g\n", v = pop());
			printf("> ");
			break;
		default:
			printf("error: unkown operator %c\n", type);
			break;
		}
		cmdtype = type;
	}
	return 0;
}
