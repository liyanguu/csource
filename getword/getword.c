/* 
getword.c
*/

#include <stdio.h>
#include <ctype.h>
#include "getword.h"

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c, d;
	char *w = word;

	while (isspace(c = getch()) && c != '\n')
		;		
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {  /*name & preprocessor line*/
		for (; --lim > 0; ++w) 
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		while (--lim > 1 && (*w++ = d = getch()) != c)
			if (d == '\\' && --lim > 1)
				*w++ = getch();
	} else if (c == '/')
		if ((d = getch()) == '*')
			in_comment();
		else if (d != EOF)
			ungetch(d);
	*w = '\0';
	return c;
}

void in_comment(void) {
	int c, d;

	c = getch();
	d = getch();
	while (c != '*' || d != '/') {
		c = d;
		d = getch();
	}
}

int buf[BUFSIZE];
int bufp = 0;

/* getch and ungetch */
int getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >=  BUFSIZE)
		printf("buffer is full, %c is not pushed", c);
	else
		buf[bufp++] = c; 
}
