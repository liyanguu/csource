/* dynamic version */

#include <stdio.h>
#include "str.h"
#include "string.h"
#include <stdlib.h>

#define MAXLEN 80 

int getlin(char s[], int len);
void copy(char dst[], char src[]);

main() {
	int n;
	int len; /* line length so far */
	int max; /* maximum line length so far */
	char line[MAXLEN+1];
	char *tmp; 
	char *longest; 

	max = len = 0;
	longest = malloc(1);
	longest[0] = '\0';
	while ((n = getlin(line, MAXLEN)) > 0) {
		len += n;
		if (len > max) {
			max = len;
			tmp = malloc(len + 1);
			strcpy(tmp, longest);
			strcat(tmp, line);
			free(longest);
			longest = tmp;
		}
		if (line[n-1] == '\n')
			len = 0;
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
