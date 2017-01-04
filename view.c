#include <stdio.h> 
#include <ctype.h>

#define MAXLINE 16

main() {
	int c, n = 0;

	printf("%.6o", n);
	while ((c = getchar()) != EOF) {
		if (isgraph(c) || c == ' ')
			printf(" %3c", c);
		else if (c == '\n')
			printf("  \\n");
		else if (c == '\t')
			printf("  \\t");
		else if (c == '\0')
			printf("  \\0");
		else
			printf(" %.3o", c);
		if (++n % MAXLINE == 0)
			printf("\n%.6o", n);
	}
	printf("\n%.6o\n", n);
	return 0;
}
