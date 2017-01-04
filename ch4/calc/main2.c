/*
main2.c - only one char push-back 
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isspace(), isdigit() */
#include <math.h> /* for sin(), exp(), pow() */
#include <string.h> /* for strcmp() */

#define MAXOP 100
#define NUMBER '0' 
#define NAME 'n'
#define VAR 'A'
#define MAXVAR 26

void mathfnc(char *);
int getop(char *);
void push(double);
double pop(void);
double top(void);
void swap(void);
void dup(void);
void clear(void);

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
			printf("\t%.8g\n", v = top());
			break;
		case 's':
			swap();
			break;
		case 'd':
			dup();
			break;
		case 'c':
			clear();
			break;
		case '\n':
			printf("\t%.8g\n", v = pop());
			printf("> ");
			break;
		default:
			printf("error: unkown operator %s\n", cmd);
			break;
		}
		var = *cmd;
	}
	return 0;
}

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

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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

void dup(void) {
	push(top());
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

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char *s) {
	char c;

	while ((*s = c = getch()) == ' ' || *s == '\t')
		;
	*(s+1) = '\0';
	if (isupper(c))
		return VAR;
	if (!islower(c) && !isdigit(c) && c != '.' && c != '-')
		return c;
	if (islower(c)) {
		if (!islower(*++s = getch())) {
			if (*s != EOF)
				ungetch(*s);
			*s = '\0';
			return c;
		}
		while (islower(*++s = getch()))
			;
		if (*s != EOF)
			ungetch(*s);
		*s = '\0';
		return NAME;
	}
	if (c == '-' && !isdigit(*++s = getch()) && *s != '.') {
		if (*s != EOF)
			ungetch(*s);
		*s = '\0';
		return c;
	}
	if (isdigit(*s))
		while (isdigit(*++s = getch()))
			;
	if (*s == '.')
		while (isdigit(*++s = getch()))
			;
	if (*s != EOF)
		ungetch(*s);
	*s = '\0';
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
