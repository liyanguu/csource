/* wl.c - print a histogram of word length in input
   2016-3-7 * */

#include <stdio.h>
#include <ctype.h>

#define IN 0
#define OUT 1
#define MAXLEN 10
#define MAXBAR 50
#define LMARGIN "           "

main() {
	int c, i, j, state, len;
	double nw[MAXLEN], total, max;

	for (i = 0; i < MAXLEN; ++i)
		nw[i] = 0;

	total = len = 0;
	state = OUT;
	while ((c = getchar()) != EOF)
		if (!isspace(c)) {
			state = IN;
			++len;
		} else if (state == IN) {
			state = OUT;
			++total;
			if (len < MAXLEN)
				++nw[len-1];
			else
				++nw[MAXLEN-1];
			len = 0;
		}
	max = 0;
	for (i = 0; i < MAXLEN; ++i)
		if (nw[i] > max)
			max = nw[i];

	for (j = MAXBAR; j > 0; --j) {
		printf(LMARGIN);
		for (i = 0; i < MAXLEN; ++i)
			if (nw[i] / max * MAXBAR >= j)
				printf(" %5c", '-');
			else
				printf(" %5c", ' ');
		putchar('\n');
	}
	printf("word length:");
	for (i = 0; i < MAXLEN; ++i)
		printf(" %5.0f", nw[i]);
	printf(" total: %5.0f\n", total);
}
