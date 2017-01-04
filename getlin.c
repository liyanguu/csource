#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getlin.h"

int getlin(char *s, int len) {
	int c;
	char *p = s;

	while (--len > 0 && (c = getchar()) != EOF && c != '\n')
		*p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return p - s;
}

#define MAXLEN 2000

int readlines(char *line[], int lim) {
	int len;
	char **t = line, *p, s[MAXLEN];

	while ((len = getlin(s, MAXLEN)) > 0)
		if (--lim < 0 || (p = malloc(len)) == NULL)
			return -1;
		else {
			s[len-1] = '\0';
			strcpy(p, s);
			*line++ = p;
		}
	return line - t;
}

int readlinesa(char *line[], int lim, char *linebuf, int bufsize) {
	int len, i;
	char **t = line, *linep = linebuf, s[MAXLEN];
	
	while ((len = getlin(s, MAXLEN)) > 0)
		if (--lim < 0 || linep + len > linebuf + bufsize)
			return -1;
		else {
			s[len-1] = '\0';
			strcpy(linep, s);
			*line++ = linep;
			linep += len;
		}
	return line - t;
}

void writelines(char *lineptr[], int lim, int decr) {
	if (decr)
		for (lineptr += lim-1; lim-- > 0; )
			printf("%s\n", *lineptr--);
	else
		while (lim-- > 0)
			printf("%s\n", *lineptr++);
}
