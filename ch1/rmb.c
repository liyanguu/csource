/* rmb.c - reduce multiple blanks in input to one */

#include <stdio.h>
#define NONBLNK 'a'

main() {
	char c, tmp;

	for (tmp = NONBLNK; (c = getchar()) != EOF; tmp = c)
		if (c != ' ' || c != tmp)
			putchar(c);
}
