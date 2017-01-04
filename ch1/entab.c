/* entab.c - replace strings of blanks by minimum
	number of tabs and blanks */

#include <stdio.h>
#include "str.h"

#define TSIZE 8

void settab(int argc, char *argv[]);
int tabpos(int);
void entab();
void detab();

main(int argc, char *argv[]) {
	settab(argc, argv);
	if (strend(*argv, "entab"))
		entab();
	else
		detab();
	return 0;
}

#define MAXTAB 1000
#define YES 1
#define NO 0
int tab[MAXTAB+1]; 

void settab(int argc, char *argv[]) {
	int i, pos, inc;

	inc = 0;
	pos = 1;
	if (argc == 1)
		for (i = 1; i <= MAXTAB; ++i)
			tab[i] = (i % TSIZE == 1) ? YES : NO;
	else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
		pos = atoi(&(*++argv)[1]);
		inc = atoi(&(*++argv)[1]);
		for (i = 1; i <= MAXTAB; ++i)
			if (i != pos)
				tab[i] = NO;
			else {
				tab[i] = YES;
				pos += inc;
			}
	} else {
		for (i = 1; i <= MAXTAB; ++i)
			tab[i] = NO;
		while (--argc > 0)
			if ((pos = atoi(*++argv)) > 0 && pos <= MAXTAB)
				tab[pos] = YES; 
	}
}

int tabpos(int pos) {
	return (pos <= MAXTAB) ? tab[pos] : YES;
}

void entab() {
	int i, c;
	int pos; /* next position in a line */
	int nb; /* number of blanks encountered */

	nb = 0;
	pos = 1;
	while ((c = getchar()) != EOF)
		if (c != ' ') {
			if (c == '\t') {
				nb = 0;
				while (tabpos(++pos) != YES)
					;
			} else if (c == '\n')
				pos = 1;
			else
				++pos;
			for ( ; nb > 0; --nb)
				putchar(' ');
			putchar(c);
		} else if (tabpos(++pos) == YES) {
			nb = 0;
			putchar('\t');
		} else
			++nb;
}

void detab() {
	int c;
	int pos = 1; /* character position in a line, start at 1 */
	int nb; /* number of blanks added to reach the next tab stop */

	while ((c = getchar()) != EOF)
		if (c == '\t')
			do
				putchar(' ');
			while (tabpos(++pos) != YES);
		else {
			putchar(c);
			if (c == '\n')
				pos = 1;
			else
				++pos;
		}
}
