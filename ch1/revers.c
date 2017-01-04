#include <stdio.h>
#include <string.h>
#include "getlin.h"

#define MAXLIN 100 

void revers(char *);

main() {
	char lin[MAXLIN+1];
	int i;

	while ((i = getlin(lin, MAXLIN)) > 0) { 
		lin[i-1] = '\0';
		revers(lin);
		printf("%s\n", lin);
	}
}

void revers(char *s) {
	char *p = s + strlen(s) -1;
	char temp;

	for ( ; s < p; s++, p--)
		temp = *s, *s = *p, *p = temp;
}
