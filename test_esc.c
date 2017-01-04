#include <stdio.h>

#define BUFSIZE 1000 

void unescape(char *, char *);
void escape(char *, char *);
int getlin(char *, int);

int main (void) {
	char line[BUFSIZE], buf[BUFSIZE];

	while (getlin(buf, BUFSIZE) > 0) {
		unescape(line, buf);
		printf("%s", line);
	}
	return 0;
}
