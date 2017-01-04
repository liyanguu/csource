/* print out local character set */

#include <stdio.h>
#define CHARMAX 256 

main() {
	int c;

	for (c = 0; c < CHARMAX; ++c) {
		putchar(c);
		putchar(' ');
	}
	return 0;
}
