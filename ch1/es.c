/* file name: es.c - convert input to escape sequence 
   change log: 
	2015-12-3 create */

#include <stdio.h>

main() {
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		else if (c == '\b')
			printf("\\b");
		else if (c == '\\')
			printf("\\\\");
		else
			putchar(c);
	}
}
