/* file name: sio.c

   change log:
	2015-11-18 create
	11-26 change file name from 'getnum.c' to 'inout.c' */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "sio.h"

int getint(int *pn) {
	int c, d, sign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (((d = c) == '+' || d == '-') && !isdigit(c=getch())) {
		if (c != EOF)
			ungetch(c);
		ungetch(d);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int getfloat(double *pf) {
	int c, d;
	double sign, pow;

	while (isspace(c = getch()) || isalpha(c))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1.0 : 1.0;
	if (c == '+' || c == '-') {
		d = c;
		if (!isdigit(c = getch()) && c != '.') {
			if (c != EOF)
				ungetch(c);
			ungetch(d);
			return 0;
		}
	}
	for (*pf = 0.0, pow = 1.0; isdigit(c); c = getch())
		*pf = 10.0 * *pf + (c - '0');
	if (c == '.')
		for ( ; isdigit(c = getch()); pow *= 10.0)
			*pf = 10.0 * *pf + (c - '0');
	*pf *= sign / pow;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 1024	/* size for read buf and getch/ungetch */

static char buf[BUFSIZE];
static int bufp = 0;

/* getch and ungetch */
int getch(void) {
	return bufp > 0 ? (signed char) buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >=  BUFSIZE)
		fprintf(stderr,
			"buffer is full, %c is not pushed\n", c);
	else
		buf[bufp++] = c; 
}

int fgetnum(int *pn, FILE *fd) {
	int c, sign;

	while (isspace(c = getc(fd)))
		;
	sign = c == '-' ? -1 : 1;
	if (c == '-' || c == '+')
		c = getc(fd);
	if (!isdigit(c) && c != EOF) {
		ungetc(c, fd);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getc(fd))
		*pn = *pn * 10 + (c - '0');
	*pn = *pn * sign;
	if (c != EOF)
		ungetc(c, fd);
	return c;
}

int getlin(char *s, int len) {
	int c;
	char *p;

	for (p = s; --len > 0 && (c = getchar()) != EOF && c != '\n'; )
		*p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return p - s;
}	

/* getl: fgets version */
int getl(char *s, int len) {
	if (fgets(s, len, stdin) == NULL)
		return 0;
	else
		return strlen(s);
}
