#include <stdio.h>
#include "table_lookup.h"
#include "getword.h"


void getdefn(char *);
void check(char *);

main() {
	int c;
	char word[100];
	
	while ((c=getch()) != EOF) {
		if (isspace(c)) {
			putchar(c);
			continue;
		} else
			ungetch(c);
		if ((c = getword(word, 100)) == '#') {
			if (strcmp(word, "#define")==0) {
				getword(word, 100);
				getdefn(word);
			} else if (strcmp(word, "#undef") == 0) {
				getword(word, 100);
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
	int c;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	for (*p++ = c; (c = getch()) != EOF && c != '\n'; )
		*p++ = (c == '\\') ? getch() : c;
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
