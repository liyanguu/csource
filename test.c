/*
file name: test.c
change log:
	2015-11-23 test getstring strleng ok! copystr copynstr ok!
	11-29 test revstr revstr2
	11-30 test revstr revstr2 ok!
	12-1  test num2str
*/

#include <stdio.h>
#include "str.h"
#include "sio.h"

#define LEN 40 

void printf(char *, ...);

main(int argc, char **argv) {
	char line[LEN], *p;
	int n;

	while ((n = getl(line, LEN)) > 0) {
		if ((p = strindex(line, argv[1])) != NULL)
			printf("%s\n", p);
		if ((p = strrindex(line, argv[1])) != NULL)
			printf("%s\n", p);
		printf("%d\n", cmpnstr(line, argv[1], 5));
	}
	return 0;
}

void printf(char *fmt, ...) {
}
