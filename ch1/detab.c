/* detab.c - replace tabs with blanks */

#include <stdio.h>
#define TSIZE 8

main(int argc, char *argv[]) {
	int c;
	int pos = 0; /* next position in a line, start at 0 */
	int nb; /* number of blanks added to reach the next tab stop */

	while ((c = getchar()) != EOF)
		if (c == '\t')
			for (nb = TSIZE - pos % TSIZE; nb > 0; --nb, ++pos)
				putchar(' ');
		else {
			putchar(c);
			if (c == '\n')
				pos = 0;
			else
				++pos;
		}
	return 0;
}
