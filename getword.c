/* 
getword.c

log:
	8-28 add getint	
*/

#include <stdio.h>
#include <ctype.h>
#include "sio.h"

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c, d;
	char *w = word;
	void in_comment(void);

	if (isalpha(c) || c == '_' || c == '#') {  /*name & preprocessor line*/
		for (*w++ = c ; --lim > 0; ++w) 
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		while (--lim > 0 && (*w++ = d = getch()) != c)
			if (d == '\\' && --lim > 0)
				*w++ = getch();
	} else if (c == '/') {
		if ((d = getch()) == '*') {
			in_comment();
		} else {
			*w++ = c;
			ungetch(d);
		}
	} else if (c != EOF)
		*w++ = c;
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
