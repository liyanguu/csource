/*******************************************************************
* TITLE: longest.c
*
* FUNCTION: printout the longest line of standard input
*
* CHANGE LOG:
*	2015-4-14 copy from THE C PROGRAMMING LANGUAGE 2ND EDITION
*	2016-3-2  print out the corrent line length and as much as
*		  possible of the text
*       2016-8-5  modify how to get line length
********************************************************************/

#include <stdio.h>

#define MAXLEN 80 

int getlin(char s[], int len);
void copy(char dst[], char src[]);

main() {
	int c, n;
	int max; /* maximum line length so far */
	char line[MAXLEN];
	char longest[MAXLEN]; 

	max = 0;
	while ((n = getlin(line, MAXLEN)) > 0) {
		if (line[n-1] != '\n') {
			while ((c = getchar()) != '\n' && c != EOF)
				++n;
			if (c == '\n')
				++n;
		}
		if (n > max) {
			max = n;
			copy(longest, line);
		}
	}

	if (max > 0)	/* there was a line */
		printf("%s\n%d\n", longest, max);	
	return 0;
}

int getlin(char s[], int len) {
	int i, c;

	for (i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}	

void copy(char dst[], char src[]) {
	int i;

	for (i = 0; (dst[i] = src[i]) != '\0'; ++i)
		;
}
