#include <stdio.h>
#include <ctype.h>
#include "str.h"

main(int argc, char *argv[]) {
	int c;

	if (strend(argv[0], "lower"))
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	return 0;
}
