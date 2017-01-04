#include <stdio.h>
#include "table_lookup.h"
#include "getword.h"

#define MAXWORD 100

void getdefn(char *);
void check(char *);

main() {
	int c;
	char word[MAXWORD];
	
	while ((c=getch()) != EOF) {
		if (isspace(c)) {
			putchar(c);
			continue;
		} else
			ungetch(c);
		if ((c = getword(word, MAXWORD)) == '#') {
			if (strcmp(word, "#define")==0) {
				getword(word, MAXWORD);
				getdefn(word);
			} else if (strcmp(word, "#undef") == 0) {
				getword(word, MAXWORD);
				undef(word);
			} else
				printf("%s", word);
		} else if (c == '\'' || c == '"') {
			printf("%s", word);
		} else if (isalpha(c) || c == '_') 
			check(word);
		else
			printf("%s", word);
	}
	return 0;
}

void getdefn(char *w) {
	char def[1000];
	char *p = def;
	int c, d;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	for (*p++ = c; (c = getch()) != EOF && c != '\n'; ) {
		if (c == '/') {
			if ((d=getch()) == '*') {
				for (c = getch(), d=getch(); c != '*' || d != '/'; c = d, d=getch())
					;
				continue;
			} else
				ungetch(d);
		}
		*p++ = (c == '\\') ? getch() : c;
	}
	*p = '\0';
	install(w, def);
}

void check(char *w) {
	struct nlist *p;

	if ((p=lookup(w)) != NULL)
		printf("%s", p->defn);
	else
		printf("%s", w);
}
