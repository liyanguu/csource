/* 2015-11-8 test_getnum.c */

#include <stdio.h>
#include "getnum.c"

main() {
	int n, a;

	while ((a = getnum(&n)) != EOF) {
		if (a > 0)
			printf("%d\n", n);
		else
			printf("%c\n", getcha());
	}
}
