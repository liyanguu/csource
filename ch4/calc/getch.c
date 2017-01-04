/* 2015-6-18 */
/*
   getch.c - getch() and ungetch()
*/

#include <stdio.h>

#define BUFSZ 100

static int bp = 0;
static int buf[BUFSZ];

int getch(void) {
	return bp <= 0 ? getchar() : buf[--bp];
}

void ungetch(int c) {
	if (bp >= BUFSZ)
		printf("buffer is full, can't unget character!\n");
	else if (c != EOF)
		buf[bp++] = c;
}
