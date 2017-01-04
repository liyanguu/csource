/* rbl2.c - remove tailing blanks of input line, 2nd version 
   log:
	2016-4-23 * */

#include <stdio.h>    
#include <ctype.h>
#define TABINC 8

main() {                 
	int c, len, nb;

	len = nb = 0;
	while ((c = getchar()) != EOF)
		if (!isspace(c)) {
			for ( ; nb > 0; --nb)
				putchar(' ');
			putchar(c);
			++len;
		} else if (c == '\n') {
			if (len > 0)
				putchar(c);
			len = nb = 0;
		} else if (c == '\t')
			nb += TABINC - nb % TABINC;
		else
			++nb;
}                            
