/*
main.c - main function for reverse polish calculator get commnad; 
	identify command and calculate;
log:
	 2015-6-18 
	 2016-9-1  test EOF pushed back of getch 
	      9-2  test buffered getchar */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	/* for atof() */
#include "calc.h"

#define MAXOP	100
#define MAXVAR	26	

main() {
	int type, var, i;
	double op2, v, varbuf[MAXVAR];
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
				printf("\aerror: divisor is zero!\n");
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
			push(atof(cmd));
			break;
		case '=':
			pop();
			if (isupper(var))
				varbuf[var - 'A'] = pop();
			else
				printf("error: invalid var %c\n", var);
			break;
		case VAR:
			push(varbuf[*cmd - 'A']);
			break;
		case 'v':
			push(v);
			break;
		case NAME:
			mathfnc(cmd);
			break;
		case 't':
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
			if (var == 't')
				printf("\t%.8g\n", v = top());
			else if (var != '=')
				printf("\t%.8g\n", v = pop());
			printf("> ");
			break;
		default:
			printf("\aerror: unkown operator %s\n", cmd);
			break;
		}
		var = *cmd;
	}
	return 0;
}
