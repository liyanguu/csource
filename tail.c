#include <stdio.h>
#include <stdlib.h>    /* for atoi */
#include <string.h>

#define DEFLINES 10    /* default #lines to print */
#define LINES 100      /* max #lines to print */
#define MAXLEN 1000    /* max length of an input line */

char line[MAXLEN];
char *lineptr[LINES]; 

int getlin(char*, int);

main(int argc, char *argv[]) {
	char *p;
	int first, last, len, n, nlines;
	
	if (argc == 1)
		n = DEFLINES;
	else if (argc == 2 && **++argv == '-')
		n = atoi(*argv + 1);
	else {
		printf("usage: tail -n");
		return 1;
	}
	if (n < 1 || n > LINES)
		n = LINES;
	last = nlines = 0;
	while ((len = getlin(line, MAXLEN)) > 0) {
		++nlines;
		if (lineptr[last] != NULL)
			free(lineptr[last]);
		if ((p = malloc(len)) == NULL) {
			printf("error: not enough memory\n");
			return 2;
		}
		line[len-1] = '\0';
		strcpy(p, line);
		lineptr[last] = p;
		last = (last + 1) % n;
	}   /* "last" is the next un-overwriten position */
	if (nlines > 0) {
		if (n > nlines)
			first = nlines = 0;
		else {
			first = last;
			nlines -= n;
		}
		do  {
			printf("%5d %s\n", ++nlines, lineptr[first]);
			first = (first + 1) % n;
		} while (first != last);
	}
	return 0;
}
