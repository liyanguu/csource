/* longest2.c - external variable version of longest.c */
 
#include <stdio.h>

#define MAXLEN 80 

char line[MAXLEN+1]; 
char tmp[MAXLEN+1];
char longest[MAXLEN+1]; 

int getlin(void);
void copytmp(void);
void copy(void);

main() {
	int n;
	int len; /* current line length */
	int max; /* maximum line length */

	max = len = 0;
	while ((n = getlin()) > 0) {
		len += n;
		if (len <= MAXLEN)
			copytmp();
		if (line[n-1] == '\n') {
			if (len > max) {
				max = len;
				copy();
			}
			len = 0;
		}
	}

	if(max > 0)	/* if there is a line */
		printf("%s\n%d\n", longest, max);	
}

int getlin(void) {
	int i, c;

	for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}	

void copy(void) {
	int i = 0;

	while ((longest[i] = tmp[i]) != '\0')
		++i;
}

void copytmp(void) {
	int i = 0;

	while ((tmp[i] = line[i]) != '\0')
		++i;
}
