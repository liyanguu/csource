#include <stdio.h>
#include <ctype.h>

#define MAXLEN 20 
#define TSIZE 8

main() {
	int c, pos; 

	pos = 0;
	while ((c = getchar()) != EOF)
		if (++pos >= MAXLEN) {
			if (!isspace(c)) {
				printf("-\n%c", c);
				pos = 1;
			} else if (c != '\n')
				putchar('\n');
		} else {
			putchar(c);
			if (c == '\t')
				pos += TSIZE - pos % TSIZE - 1;
		}
}
