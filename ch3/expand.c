#include <stdio.h>
#include "/home/liyang/c/include/getlin.h"

#define MAXSTR 1000

main() {
	char line[MAXSTR], linecpy[MAXSTR];

	while (getlin(line, MAXSTR) > 0) {
		expand(line, linecpy);
		printf("%s", linecpy);
	}
}
