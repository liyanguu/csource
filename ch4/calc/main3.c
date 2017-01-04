/*
main.c:
	main function for reverse polish calculator,
	get commnad, identify command and calculate
log:
	2015-6-18  * 
	2016-8-7   modify getopl
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> 
#include <math.h>   /* for sin(), exp(), pow() */
#include <string.h>

#define MAXOP 100
#define NUMBER '0' 
#define NAME 'n'
#define VAR 'A'
#define MAXVAR 26

void mathfnc(char *);
int getopl(char *);
int getop(char *);
void push(double);
double pop(void);
double top(void);
void swap(void);
void clear(void);

main() {
	int type; 
	int i;
	double op2;            
	char cmd[MAXOP];
	int var;                   /* last variable name          */
	int cmdtype;               /* last command type           */ 
	double v;                  /* most recently printed value */
	double varbuf[MAXVAR];     /* variables                   */

	for (i = 0; i < MAXVAR; ++i)
		varbuf[i] = 0.0;
	printf("> ");
	while ((type = getopl(cmd)) != EOF) {
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
			else if (cmdtype != 't' && cmdtype != 'c' &&
				cmdtype != 'd' && cmdtype != 's')	
				printf("\t%.8g\n", v = pop());
			printf("> ");
			break;
		default:
			printf("error: unkown operator %s\n", cmd);
			break;
		}
		cmdtype = type;
	}
	return 0;
}

void mathfnc(char *s) {
	double op2;

	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "cos") == 0)
		push(cos(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "pow") == 0) {
		op2 = pop();
		push(pow(pop(), op2));
	} else if (strcmp(s, "abs") == 0)
		push(fabs(pop()));
	else
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
#define MAXLINE 200

int getch(void);
void ungetch(int);

int getop(char *s) {
	static int buf = 0;
	int c;
	char *t = s;

	c = buf == 0 ? getchar() : buf;
	buf = 0;
	while ((*s = c) == ' ' || c == '\t')
		c = getchar();
	*(s+1) = '\0';
	if (isupper(c))
		return VAR;
	if (islower(c)) {
		while (islower(*++s = c = getchar()))
			;
		buf = c;
		*s = '\0';
		if (s - t > 1)
			return NAME;
		else
			return *t;
	}
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	if (c == '-' && !isdigit(*++s = c = getchar()) && c != '.') {
		buf = c;
		*s = '\0';
		return '-';
	}
	if (isdigit(c))
		while (isdigit(*++s = c = getchar()))
			;
	if (c == '.')
		while (isdigit(*++s = c = getchar()))
			;
	buf = c;
	*s = '\0';
	return NUMBER;
}

int lp = 0;
char line[MAXLINE];

int getopl(char *s) {
	char c, *t = s;
	int getlin(char *, int);

	if (line[lp] == '\0' || lp == 0)
		if (!getlin(line, MAXLINE))
			return EOF;
		else
			lp = 0;
	while ((*s = c = line[lp++]) == ' ' || c == '\t')
		;
	*(s+1) = '\0';
	if (isupper(c))
		return VAR;
	if (!isdigit(c) && c != '.' && c != '-') {
		if (islower(c)) {
			while (islower(*++s = line[lp]))
				++lp;
			*s = '\0';
		}
		return s - t > 1 ? NAME : c;
	}
	if (c == '-' && !isdigit(*++s = c = line[lp++]) && c != '.') {
		--lp;
		*s = '\0';
		return '-';
	}
	if (isdigit(c))
		while (isdigit(*++s = c = line[lp++]))
			;
	if (c == '.')
		while (isdigit(*++s = c = line[lp++]))
			;
	--lp;
	*s = '\0';
	return NUMBER;
}

int buf = 0;

int getch(void) {
	int c;

	if (buf == 0)
		c = getchar();
	else {
		c = buf;
		buf = 0;
	}
	return c;
}

void ungetch(int c) {
	if (buf != 0)
		printf("error: too many chars!\n");
	else
		buf = c;
}

void ungets(char *s) {
	int len = strlen(s);

	for (s += len; len > 0; --len)
		ungetch(*--s);
}

int getlin(char *s, int len) {
	int c; 
	char *t;

	for (t = s; len-- > 0 && (c = getchar()) != EOF && c != '\n'; )
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - t;
}	
