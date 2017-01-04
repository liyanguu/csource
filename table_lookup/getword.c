/* getword.c - get alphabetic for numeric string from std input */

/* 2015-5-4 */

#include <stdio.h>
#include <ctype.h>
#include "getword.h"

int getword(char s[], int lim) {
	int i, c, d;

	i = 0;
	while (skipcomment())
		;
	if ((c=getch()) == EOF)
		return c;
	s[0] = c;
	s[1] = '\0';
	if (c == '\'' || c == '"') {
		while (--lim > 0 && (d = getch()) != c) {
			s[++i] = d;
			if (d == '\\')
				s[++i] = getch();
		}
		s[++i] = d;
		s[++i] = '\0';
		return c;
	} 
	if (!isalpha(c) && c != '_' && c != '#')
		return c; 
	if (c == '#') {
		while (isspace(c = getch()))
			;
		s[++i] = c;
	}
	while (--lim > 0 && (isalnum(c = getch()) || c == '_'))
		s[++i] = c;
	ungetch(c);
	s[++i] = '\0';
	return s[0];
}

int skipcomment(void) {
	int c, d;

	while (isspace(c = getch()))
		;
	if (c == '/') {
		if ((d = getch()) == '*') {
			c = getch();
			d = getch();
			for ( ; c != '*' || d != '/'; c = d, d=getch())
				;
			return 1;
		} else {
			ungetch(d);
			ungetch(c);
			return 0;
		}
	} else {
		ungetch(c);
		return 0;
	}
}

#define BUFSIZE 1024	/* size for read buf and getch/ungetch */

static char buf[BUFSIZE];
static int bufp = 0;

/* getch and ungetch */
int getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >=  BUFSIZE)
		fprintf(stderr,
			"buffer is full, %c is not pushed\n", c);
	else if (c != EOF)
		buf[bufp++] = c; 
}
