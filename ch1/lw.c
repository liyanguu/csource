/* lw.c - print input one word per line 
   log:
	2016-3-13 * */

#include <stdio.h>
#include <ctype.h>

#define IN 1
#define OUT 2

main() {
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF)
		if (!isspace(c)) {
			state = IN;
			putchar(c);
		} else if (state == IN) {
			state = OUT;
			putchar('\n');
		}
}
