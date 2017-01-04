#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getop(char *s) {
	static int c = 0;
	char d;
	char *t = s;

	if (c == 0 || c == ' ' || c == '\t')
		while ((c=getchar()) == ' ' || c == '\t')
			;
	if (c != EOF)
		*s++ = c;
	*s = '\0';
	if (isupper(c)) {
		c = 0;
		return VAR;
	}
	if (!islower(c) && !isdigit(c) && c != '.' && c != '-') {
		d = c;
		c = 0;
		return d;
	}
	if (islower(c)) {
		while (islower(c = getch()))
			*s++ = c;
		*s = '\0';
		return s - t > 1 ? NAME : t[0];
	}
	if (c == '-') {
		if (!isdigit(c = getch()) && c != '.')
			return '-';
		else
			*s++ = c;
	}
	if (isdigit(c))
		while (isdigit(c = getch()))
			*s++ = c;
	if (c == '.')
		for (*s++ = c; isdigit(c = getch()); *s++ = c);
			;
	*s = '\0';
	return NUMBER;
}
