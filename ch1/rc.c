/* rc.c - remove comment */

#include <stdio.h>

void rcomment(int);
void in_comment(void);
void echo_quote(int);
void ungetch(int);
int getch(void);

main() {
	int c, d;

	while ((c = getch()) != EOF)
		if (c == '/') {
			if ((d = getch()) == '*')
				in_comment();
			else {
				putchar(c);
				if (d != EOF) 
					ungetch(d);
			}
		} else if (c == '\'' || c == '"')
			echo_quote(c);
		else
			putchar(c);
	return 0;	
}

void rcomment(int c) {
	int d;

	if (c == '/')
		if ((d = getchar()) == '*')
			in_comment();
		else if (d == '/') { 
			putchar(d);
			rcomment(d);
		} else {
			putchar(c);
			putchar(d);
		}
	else if (c == '\'' || c == '"')
		echo_quote(c);
	else
		putchar(c);
}

void echo_quote(int c) {
	int d;

	putchar(c);
	while ((d = getchar()) != c) {
		putchar(d);
		if (d == '\\') /* escaped char */
			putchar(getchar());
	}
	putchar(d);
}

void in_comment(void) {
	int c, d;

	c = getch();
	d = getch();
	while (c != '*' || d != '/') {
		c = d;
		d = getch();
	}
}

#define BUFSZ 100

static int bp = 0;
static int buf[BUFSZ];

int getch(void) {
	return bp <= 0 ? getchar() : buf[--bp];
}

void ungetch(int c) {
	if (bp >= BUFSZ)
		printf("buffer is full, can't unget character!\n");
	else
		buf[bp++] = c;
}
