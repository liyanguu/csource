#include <stdio.h>
#include <string.h>
#include "dcl.h"

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
int prevtoken = NO;

int gettoken(void) {   /* return next token */
	int c;
	char *p = token;

	if (prevtoken) {
		prevtoken = NO;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		do
			*p++ = c;
		while (isalnum(c = getch()));
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

/* get the next token and push it back */
int nexttoken(void) {
	int type;

	type = gettoken();
	prevtoken = YES;
	return type; 
}

void errmsg(char *msg) {
	prevtoken = YES;
	printf("%s", msg);
}
