#include <stdio.h>
#include "/home/liyang/c/include/getlin.h"

#define MAXLINE 1000
char line[MAXLINE], linecpy[MAXLINE];

int main() {
	while (getlin(line, MAXLINE) > 0) {
		escape(linecpy, line);
		printf("%s", linecpy);
	}
	return 0;
}
